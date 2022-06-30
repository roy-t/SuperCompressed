using static Xunit.Assert;

namespace SuperCompressed.Tests
{
    public class UnitTests
    {
        [Fact]
        public void CanLoadFortyTwo()
        {
            var ft = SuperCompressed.NativeMethods.FortyTwo();
            Equal(42, ft);
        }
    }
}