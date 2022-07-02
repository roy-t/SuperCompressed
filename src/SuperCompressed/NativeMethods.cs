using System.Runtime.InteropServices;

namespace SuperCompressed
{
    public enum Quality : byte
    {
        Fastest,
        Faster,
        Default,
        Slower,
        Slowest
    };

    public enum Mode : byte
    {
        SRgb,
        Linear,
        Normalized
    };

    public enum MipMapGeneration : byte
    {
        None,
        Full,
    };

    internal static class NativeMethods
    {
        [DllImport("SuperCompressed.Native.dll", EntryPoint = "Initialize")]
        public static unsafe extern void Initialize();

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "Deinitialize")]
        public static unsafe extern void Deinitialize();


        [DllImport("SuperCompressed.Native.dll", EntryPoint = "Encode")]
        public static unsafe extern CompressedTexture Encode(byte* buffer, int components, int width, int heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality);

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "Free")]
        public static unsafe extern void Free(byte* buffer);
    }

    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct CompressedTexture
    {
        public int ErrorCode { get; }
        public int SizeInBytes { get; }
        public byte* Buffer { get; }
    };

    public sealed class Texture
    {
        public Texture(byte[] data, int components, int width, int height)
        {
            Data = data;
            Components = components;
            Width = width;
            Height = height;
        }

        public byte[] Data { get; }
        public int Components { get; }
        public int Width { get; }
        public int Height { get; }
    }

    public sealed class CompressedTextureData
    {
        internal unsafe CompressedTextureData(byte* data, int length)
        {
            this.Data = new byte[length];

            var span = new ReadOnlySpan<byte>(data, length);
            span.CopyTo(this.Data);
        }

        public byte[] Data { get; }
    }

    public static class CoolMethods
    {
        public unsafe static CompressedTextureData Encode(Texture texture, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
        {
            fixed (byte* pData = &MemoryMarshal.GetArrayDataReference(texture.Data))
            {
                var data = new CompressedTexture();
                try
                {
                    NativeMethods.Initialize();

                    data = NativeMethods.Encode(pData, texture.Components, texture.Width, texture.Height, mode, mipMapGeneration, quality);

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
