using static Xunit.Assert;

namespace SuperCompressed.Tests
{
    public class UnitTests
    {
        [Fact]
        public void CanLoadFortyTwo()
        {
            var uncompressed = new Texture(new byte[4 * 32 * 32], 4, 32, 32);            
            var compressed = CoolMethods.Encode(uncompressed, Mode.SRgb, MipMapGeneration.Full, Quality.Slower);

            True(compressed.Data.Length > 0);
        }
    }
}