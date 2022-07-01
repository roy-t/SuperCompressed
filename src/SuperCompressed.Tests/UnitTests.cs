using static Xunit.Assert;

namespace SuperCompressed.Tests
{
    public class UnitTests
    {
        [Fact]
        public void CanLoadFortyTwo()
        {
            using (var texture = new Texture(new byte[100], 128, 64, 256))
            {
                var ft = SuperCompressed.CoolMethods.Encode(texture, Mode.SRgb, MipMapGeneration.Full, Quality.Slower);
                Equal(128, ft.Stride);
                Equal(64, ft.Width);
                Equal(256, ft.Height);
            }

            Console.WriteLine("Hello World!");
        }
    }
}