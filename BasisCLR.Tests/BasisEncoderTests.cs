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
            using var encoder = new Encoder();
            encoder.Dispose();
        }


        [Fact]
        public void FailsOnWrongFilename()
        {
            using var encoder = new Encoder();
            var settings = new EncoderSettings();

            Throws<Exception>(() => encoder.Encode("C:/this_file_does_not_exist.tga", settings));
        }

        [Fact]
        public void EncodeDoesSomething()
        {            
            var cwd = Directory.GetCurrentDirectory();
            var filename = Path.GetFullPath(Path.Combine(cwd, "../../../../../Assets/image_with_alpha.tga"));

            True(File.Exists(filename));

            using var encoder = new Encoder();
            var settings = new EncoderSettings();

            var bytes = encoder.Encode(filename, settings);
            
            True(bytes.Length > 0);
        }

        [Fact]
        public void AMipMappedImageShouldBeLarger()
        {
            var cwd = Directory.GetCurrentDirectory();
            var filename = Path.GetFullPath(Path.Combine(cwd, "../../../../../Assets/image_with_alpha.tga"));

            True(File.Exists(filename));

            using var encoder = new Encoder();
            var settings = new EncoderSettings()
            {
                Alpha = false,
                Mipmap = false,
                Perceptual = true,
                Threads = 8u,
                Uastc = false,
            };            

            var bytes = encoder.Encode(filename, settings);
            True(bytes.Length > 0);

            settings.Mipmap = true;

            var mipMappedBytes = encoder.Encode(filename, settings);            
            True(mipMappedBytes.Length > 0);

            True(mipMappedBytes.Length > bytes.Length);
        }
    }
}