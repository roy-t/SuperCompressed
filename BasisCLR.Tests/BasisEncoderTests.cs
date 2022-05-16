using SuperCompressed.BasisUniversal;
using System;
using Xunit;
using static Xunit.Assert;

namespace BasisCLR.Tests
{
    public class BasisEncoderTests
    {
        [Fact]
        public void CanCreateAndDestroy()
        {
            var encoder = new Encoder();
            encoder.Dispose();
        }


        [Fact]
        public void FailsOnWrongFilename()
        {
            using var encoder = new Encoder();
            Throws<Exception>(() => encoder.Encode("C:/this_file_does_not_exist.tga"));
        }
    }
}