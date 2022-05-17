using SuperCompressed.BasisUniversal;
using System;
using System.IO;
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

        [Fact]
        public void EncodeDoesSomething()
        {            
            var cwd = Directory.GetCurrentDirectory();
            var filename = Path.GetFullPath(Path.Combine(cwd, "../../../../../Assets/image_with_alpha.tga"));

            True(File.Exists(filename));

            using var encoder = new Encoder();
            var bytes = encoder.Encode(filename);
            
            True(bytes.Length > 0);
        }
    }
}