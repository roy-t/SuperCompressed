using static Xunit.Assert;

namespace SuperCompressed.Tests
{
    public class UnitTests
    {
        [Fact]
        public void CanLoadImageData()
        {
            var filename = TestUtilities.GetTestFilename();
            var uncompressed = Image.FromStream(File.OpenRead(filename));

            var encoder = Encoder.Instance;
            var compressed = encoder.Encode(uncompressed, Mode.SRgb, MipMapGeneration.Full, Quality.Slower);

            True(compressed.Data.Length > 0);
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