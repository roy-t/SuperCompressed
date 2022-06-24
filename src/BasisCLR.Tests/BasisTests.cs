using LibKtxDotNet;
using SuperCompressed.BasisUniversal;
using System;
using System.IO;
using Xunit;
using static Xunit.Assert;

namespace BasisCLR.Tests
{
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

    public sealed class KtxTexts
    {
        [Fact]
        public void Should()
        {
            string filename = TestUtilities.GetTestFilename();
            var value = NativeMethods.ktxTexture_CreateFromNamedFile(filename, ktxTextureCreateFlagBits.KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT, out var ptrTo);

            True(value == ktx_error_code_e.KTX_SUCCESS);
            True(ptrTo != IntPtr.Zero);
        }
    }

    public sealed class BasisTests : IDisposable
    {
        private readonly Encoder Encoder;
        private readonly Transcoder Transcoder;

        public BasisTests()
        {
            this.Encoder = new Encoder();
            this.Transcoder = new Transcoder();
        }

        [Fact]
        public void WrongFilename()
        {        
            Throws<Exception>(() => this.Encoder.EncodeEtc1s("C:/this_file_does_not_exist.tga"));
            Throws<Exception>(() => this.Encoder.EncodeUastc("C:/this_file_does_not_exist.tga"));
        }

        [Fact]
        public void EncodeEtc1s()
        {
            string filename = TestUtilities.GetTestFilename();            
            var bytes = this.Encoder.EncodeEtc1s(filename);

            True(bytes.Length > 0);
        }

        [Fact]
        public void TranscodeEtc1s()
        {
            string filename = TestUtilities.GetTestFilename();
            var encodedBytes = this.Encoder.EncodeEtc1s(filename, generateMipmaps: true);

            True(encodedBytes.Length > 0);

            var imageCount = this.Transcoder.GetImageCount(encodedBytes);
            True(imageCount == 1);            

            var mipmapCount = this.Transcoder.GetMipMapCount(encodedBytes, 0);
            True(mipmapCount == 8);

            var transcodedBytes = this.Transcoder.Transcode(encodedBytes, 0, 0, out var width, out var height, out var pitch);

            True(transcodedBytes.Length > 0);
            True(transcodedBytes.Length >= encodedBytes.Length);
        }        

        public void Dispose()
        {
            this.Encoder.Dispose();
            this.Transcoder.Dispose();
        }
    }
}