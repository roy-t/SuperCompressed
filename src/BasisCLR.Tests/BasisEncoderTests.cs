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
        public void CreateAndDestroy()
        {
            using var encoder = new Encoder();
            encoder.Dispose();
        }


        [Fact]
        public void WrongFilename()
        {
            using var encoder = new Encoder();

            Throws<Exception>(() => encoder.Encode("C:/this_file_does_not_exist.tga"));
        }

        [Fact]
        public void Encode()
        {
            string filename = GetTestFilename();            
            using var encoder = new Encoder();
            var bytes = encoder.Encode(filename);

            True(bytes.Length > 0);
        }       

        [Fact]
        public void Transcode()
        {
            string filename = GetTestFilename();
            using var encoder = new Encoder();
            var encodedBytes = encoder.Encode(filename);

            True(encodedBytes.Length > 0);

            using var transcoder = new Transcoder();
            var transcodedBytes = transcoder.Transcode(encodedBytes, filename);

            True(transcodedBytes.Length > 0);
            True(transcodedBytes.Length >= encodedBytes.Length);
        }

        private static string GetTestFilename()
        {
            var cwd = Directory.GetCurrentDirectory();
            var filename = Path.GetFullPath(Path.Combine(cwd, "../../../../image_with_alpha.tga"));
            
            True(File.Exists(filename));

            return filename;
        }

    }
}