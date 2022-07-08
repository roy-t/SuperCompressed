using System.Runtime.InteropServices;
using ZstdSharp;

namespace SuperCompressed
{
    public sealed class Encoder
    {
        private static Encoder? instance;
        public static Encoder Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new Encoder();
                }
                return instance;
            }
        }

        Encoder()
        {
            NativeEncoder.InitializeEncoder();
        }

        ~Encoder()
        {
            NativeEncoder.DeinitializeEncoder();
        }

        private static ReadOnlySpan<byte> Compress(ReadOnlySpan<byte> texture)
        {
            using var compressor = new Compressor(-1);
            return compressor.Wrap(texture);
        }

        public unsafe ReadOnlySpan<byte> Encode(Image texture, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
        {
            fixed (byte* pData = &MemoryMarshal.GetReference(texture.Data))
            {
                var data = NativeEncoder.Encode(pData, texture.ComponentCount, texture.Width, texture.Height, mode, mipMapGeneration, quality);

                if (data.ErrorCode != EncodeErrors.None)
                {
                    throw new Exception($"Encoder failed: {data.ErrorCode}");
                }

                var span = new Span<byte>(data.Buffer, data.Length);                
                return Compress(span);
            }
        }
    }
}