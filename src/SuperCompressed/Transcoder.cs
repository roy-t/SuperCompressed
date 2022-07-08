using System.IO.Compression;
using System.Runtime.InteropServices;

namespace SuperCompressed
{
    public sealed class Transcoder
    {
        private static Transcoder? instance;
        public static Transcoder Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new Transcoder();
                }
                return instance;
            }
        }

        Transcoder()
        {
            NativeTranscoder.InitializeTranscoder();
        }

        private static ReadOnlySpan<byte> Decompress(ReadOnlySpan<byte> texture)
        {
            var originalLength = BitConverter.ToInt32(texture.Slice(0, 4));
            var decompressed = new byte[originalLength];

            if (BrotliDecoder.TryDecompress(texture.Slice(4), decompressed, out var written))
            {
                if(written == originalLength)
                {
                    return decompressed;
                }                
            }

            throw new Exception($"Failed to decompress texture data");
        }

        public unsafe int GetImageCount(ReadOnlySpan<byte> texture)
        {
            var textureData = Decompress(texture);

            fixed (byte* pData = &MemoryMarshal.GetReference(textureData))
            {
                var imageCount = NativeTranscoder.GetImageCount(pData, textureData.Length);
                if (imageCount >= 0)
                {
                    return imageCount;
                }

                throw new Exception($"Transcoder failed: {(TranscodeErrors)(imageCount * 1)}");
            }
        }

        public unsafe int GetLevelCount(ReadOnlySpan<byte> texture, int imageIndex)
        {
            var textureData = Decompress(texture);

            fixed (byte* pData = &MemoryMarshal.GetReference(textureData))
            {
                var levelCount = NativeTranscoder.GetLevelCount(pData, textureData.Length, imageIndex);
                if (levelCount >= 0)
                {
                    return levelCount;
                }

                throw new Exception($"Transcoder failed: {(TranscodeErrors)(levelCount * 1)}");
            }
        }

        public unsafe TranscodedTextureData Transcode(ReadOnlySpan<byte> texture, int imageIndex, int levelIndex, TranscodeFormats targetFormat)
        {
            var textureData = Decompress(texture);

            fixed (byte* pData = &MemoryMarshal.GetReference(textureData))
            {
                var data = NativeTranscoder.Transcode(pData, textureData.Length, imageIndex, levelIndex, targetFormat);

                if (data.ErrorCode != TranscodeErrors.None)
                {
                    throw new Exception($"Transcoder failed: {data.ErrorCode}");
                }

                return new TranscodedTextureData(data.Buffer, data.Length, data.Width, data.Heigth, data.Pitch, targetFormat);

            }
        }
    }
}
