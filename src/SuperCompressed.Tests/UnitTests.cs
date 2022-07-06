using static Xunit.Assert;

namespace SuperCompressed.Tests
{
    public class UnitTests
    {
        [Fact]
        public void CanLoadImageData()
        {
            var filename = TestUtilities.GetTestFilename();
            var image = Image.FromStream(File.OpenRead(filename));

            var encoder = Encoder.Instance;
            var encoded = encoder.Encode(image, Mode.SRgb, MipMapGeneration.Full, Quality.Slower);

            True(encoded.Data.Length > 0);
        }


        [Fact]
        public void CanTranscodeImageData()
        {
            var filename = TestUtilities.GetTestFilename();
            var uncompressed = Image.FromStream(File.OpenRead(filename));

            var encoder = Encoder.Instance;
            var compressed = encoder.Encode(uncompressed, Mode.SRgb, MipMapGeneration.Full, Quality.Slower);

            True(compressed.Data.Length > 0);


            var transcoder = Transcoder.Instance;
            var images = transcoder.GetImageCount(compressed.Data);

            Equal(1, images);

            var levels = transcoder.GetLevelCount(compressed.Data, 0);

            Equal(8, levels);

            var transcoded = transcoder.Transcode(compressed.Data, 0, 0, TranscodeFormats.BC7_RGBA);

            True(transcoded.Data.Length > 0);
            True(transcoded.Pitch > 0);
            Equal(128, transcoded.Width);
            Equal(128, transcoded.Heigth);
            Equal(TranscodeFormats.BC7_RGBA, transcoded.Format);            
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