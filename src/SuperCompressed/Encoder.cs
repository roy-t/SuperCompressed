using System.Runtime.InteropServices;

namespace SuperCompressed
{            
    public class Encoder
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
            NativeMethods.Initialize();
        }

        ~Encoder()
        {
            NativeMethods.Deinitialize();
        }

        public unsafe CompressedTextureData Encode(Image texture, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
        {
            fixed (byte* pData = &MemoryMarshal.GetReference(texture.Data))
            {
                var data = new CompressedTexture();
                try
                {
                    NativeMethods.Initialize();

                    data = NativeMethods.Encode(pData, texture.ComponentCount, texture.Width, texture.Height, mode, mipMapGeneration, quality);

                    if (data.ErrorCode != 0)
                    {
                        throw new Exception($"Encoder failed: {data.ErrorCode}");
                    }

                    return new CompressedTextureData(data.Buffer, data.SizeInBytes);
                }
                finally
                {
                    if (data.ErrorCode == 0)
                    {
                        NativeMethods.Free(data.Buffer);
                    }

                    NativeMethods.Deinitialize();
                }
            }
        }
    }
}