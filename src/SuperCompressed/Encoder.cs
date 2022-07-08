using System.IO.Compression;
using System.Runtime.InteropServices;

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
            var max = BrotliEncoder.GetMaxCompressedLength(texture.Length);
            var compressed = new byte[max];
            // Level 9 seems to give the best decompression speed, while still having a reasonable compression speed
            // https://paulcalvano.com/2018-07-25-brotli-compression-how-much-will-it-reduce-your-content/
            if (BrotliEncoder.TryCompress(texture, compressed, out var written, 9, 24))
            {
                return new ReadOnlySpan<byte>(compressed, 0, written);                
            }

            throw new Exception($"Failed to decompress texture data");
        }

        public unsafe byte[] Encode(Image texture, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
        {
            fixed (byte* pData = &MemoryMarshal.GetReference(texture.Data))
            {
                var data = NativeEncoder.Encode(pData, texture.ComponentCount, texture.Width, texture.Height, mode, mipMapGeneration, quality);

                if (data.ErrorCode != EncodeErrors.None)
                {
                    throw new Exception($"Encoder failed: {data.ErrorCode}");
                }

                var span = new Span<byte>(data.Buffer, data.Length);                
                var compressed = Compress(span);

                var compressedBytes = new byte[compressed.Length + 4];
                compressed.CopyTo(new Span<byte>(compressedBytes, 4, compressedBytes.Length - 4));

                var length = BitConverter.GetBytes(data.Length);
                compressedBytes[0] = length[0];
                compressedBytes[1] = length[1];
                compressedBytes[2] = length[2];
                compressedBytes[3] = length[3];

                return compressedBytes;
            }
        }
    }
}