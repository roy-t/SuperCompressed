using Xunit;
using SuperCompressed.BasisUniversal;

namespace BasisCLR.Tests
{
    public class BasisEncoderTests
    {
        [Fact]
        public void CanCreateAndDestroy()
        {
            var encoder = new BasisEncoder();
            encoder.Dispose();            
        }
    }
}