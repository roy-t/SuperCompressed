using BigGustave;
using static Xunit.Assert;

namespace SuperCompressed.Tests
{
    public class UnitTests
    {
        [Fact]
        public void CanEncodeImageData()
        {
            var filename = TestUtilities.GetTestFilename();
            var image = Image.FromStream(File.OpenRead(filename));

            var encoder = Encoder.Instance;
            var encoded = encoder.Encode(image, Mode.SRgb, MipMapGeneration.Default, Quality.Slower);

            True(encoded.Length > 0);
        }

        [Fact]
        public void ShowFilterDifferences()
        {
            var filename = TestUtilities.GetTestFilename();
            var uncompressed = Image.FromStream(File.OpenRead(filename));
            var encoder = Encoder.Instance;
            var transcoder = Transcoder.Instance;

            var formats = Enum.GetValues<MipMapGeneration>();

            //var formats = new MipMapGeneration[] { MipMapGeneration.Default };

            foreach (var format in formats)
            {
                if(format == MipMapGeneration.Disabled) { continue; }

                var encoded = encoder.Encode(uncompressed, Mode.SRgb, format, Quality.Slower);
                using var transcoded = transcoder.Transcode(encoded, 0, 2, TranscodeFormats.RGBA32);

                using var stream = File.Create($"{format}-{transcoded.Width}x{transcoded.Heigth}.png");
                CreatePng(stream, transcoded.Width, transcoded.Heigth, transcoded.Data.ToArray());
            }
        }


        private void CreatePng(FileStream stream, int width, int height, byte[] pixels)
        {
            var builder = PngBuilder.FromBgra32Pixels(pixels, width, height, false);
            builder.Save(stream);
            
            //for (var i = 0; i < pixels.Length; i += 4)
            //{
            //    var r = pixels[i + 0];
            //    var g = pixels[i + 1];
            //    var b = pixels[i + 2];
            //    var a = pixels[i + 3];


            //    var x = i % width;
            //    var y = i / width;

            //    builder.SetPixel(r, g, b, x, y);

            //}

            //builder.Save(stream);            
        }

        [Fact]
        public void CanTranscodeImageData()
        {
            var filename = TestUtilities.GetTestFilename();
            var uncompressed = Image.FromStream(File.OpenRead(filename));

            var encoder = Encoder.Instance;
            var encoded = encoder.Encode(uncompressed, Mode.SRgb, MipMapGeneration.Lanczos4, Quality.Slower);

            True(encoded.Length > 0);


            var transcoder = Transcoder.Instance;
            var images = transcoder.GetImageCount(encoded);

            Equal(1, images);

            var levels = transcoder.GetLevelCount(encoded, 0);

            Equal(8, levels);


            var formats = Enum.GetValues<TranscodeFormats>();

            foreach (var targetFormat in formats)
            {
                foreach (var imageIndex in Enumerable.Range(0, images))
                {
                    foreach (var levelIndex in Enumerable.Range(0, levels))
                    {
                        using var transcoded = transcoder.Transcode(encoded, imageIndex, levelIndex, targetFormat);
                        True(transcoded.Data.Length > 0);
                        Equal(128 >> levelIndex, transcoded.Width);
                        Equal(128 >> levelIndex, transcoded.Heigth);
                        Equal(targetFormat, transcoded.Format);

                        // For compressed formats the pitch is only > 0 if the the size of the image is larger than
                        // the block size, for uncompressed formats the block size is 1x1 so there's no such exception
                        if (transcoded.Width >= 4)
                        {
                            True(transcoded.Pitch > 0);
                        }
                    }
                }
            }
        }

        public static class TestUtilities
        {
            public static string GetTestFilename()
            {
                var cwd = Directory.GetCurrentDirectory();
                var filename = Path.GetFullPath(Path.Combine(cwd, "../../../../image_with_alpha.tga"));

                True(File.Exists(filename));

                return filename;
            }
        }
    }
}