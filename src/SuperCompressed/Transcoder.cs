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

        public unsafe int GetImageCount(ReadOnlySpan<byte> texture)
        {
            fixed (byte* pData = &MemoryMarshal.GetReference(texture))
            {
                var imageCount = NativeTranscoder.GetImageCount(pData, texture.Length);
                if (imageCount >= 0)
                {
                    return imageCount;
                }

                throw new Exception($"Transcoder failed: {(TranscodeErrors)(imageCount * 1)}");
            }
        }

        public unsafe int GetLevelCount(ReadOnlySpan<byte> texture, int imageIndex)
        {
            fixed (byte* pData = &MemoryMarshal.GetReference(texture))
            {
                var levelCount = NativeTranscoder.GetLevelCount(pData, texture.Length, imageIndex);
                if (levelCount >= 0)
                {
                    return levelCount;
                }

                throw new Exception($"Transcoder failed: {(TranscodeErrors)(levelCount * 1)}");
            }
        }

        public unsafe TranscodedTextureData Transcode(ReadOnlySpan<byte> texture, int imageIndex, int levelIndex, TranscodeFormats targetFormat)
        {
            fixed (byte* pData = &MemoryMarshal.GetReference(texture))
            {
                var data = new TranscodedTexture();
                try
                {
                    data = NativeTranscoder.Transcode(pData, texture.Length, imageIndex, levelIndex, targetFormat);

                    if (data.ErrorCode != TranscodeErrors.None)
                    {
                        throw new Exception($"Transcoder failed: {data.ErrorCode}");
                    }

                    return new TranscodedTextureData(data.Buffer, data.Length, data.Width, data.Heigth, data.Pitch, targetFormat);
                }
                finally
                {
                    if (data.ErrorCode == 0)
                    {
                        NativeTranscoder.FreeTranscodedTexture(data);
                    }
                }
            }
        }
    }
}
