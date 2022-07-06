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
            using var encoded = encoder.Encode(image, Mode.SRgb, MipMapGeneration.Full, Quality.Slower);

            True(encoded.Data.Length > 0);
        }

        [Fact]
        public void CanTranscodeImageData()
        {
            var filename = TestUtilities.GetTestFilename();
            var uncompressed = Image.FromStream(File.OpenRead(filename));

            var encoder = Encoder.Instance;
            using var encoded = encoder.Encode(uncompressed, Mode.SRgb, MipMapGeneration.Full, Quality.Slower);

            True(encoded.Data.Length > 0);


            var transcoder = Transcoder.Instance;
            var images = transcoder.GetImageCount(encoded.Data);

            Equal(1, images);

            var levels = transcoder.GetLevelCount(encoded.Data, 0);

            Equal(8, levels);


            var formats = Enum.GetValues<TranscodeFormats>();

            foreach(var targetFormat in formats)
            {
                foreach (var imageIndex in Enumerable.Range(0, images))
                {
                    foreach (var levelIndex in Enumerable.Range(0, levels))
                    {
                        using var transcoded = transcoder.Transcode(encoded.Data, imageIndex, levelIndex, targetFormat);
                        True(transcoded.Data.Length > 0);                        
                        Equal(128 >> levelIndex , transcoded.Width);
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