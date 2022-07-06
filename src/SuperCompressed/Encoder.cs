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

        public unsafe EncodedTextureData Encode(Image texture, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
        {
            fixed (byte* pData = &MemoryMarshal.GetReference(texture.Data))
            {
                var data = NativeEncoder.Encode(pData, texture.ComponentCount, texture.Width, texture.Height, mode, mipMapGeneration, quality);

                if (data.ErrorCode != EncodeErrors.None)
                {
                    throw new Exception($"Encoder failed: {data.ErrorCode}");
                }

                return new EncodedTextureData(data.Buffer, data.Length);
            }
        }
    }
}