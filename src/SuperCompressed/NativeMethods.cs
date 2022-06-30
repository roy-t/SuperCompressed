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
        [DllImport("SuperCompressed.Native.dll", EntryPoint = "Encode")]
        public static unsafe extern CompressedTexture Encode(byte* buffer, int width, int heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality);

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "Free")]
        public static unsafe extern void Free(byte* buffer);
    }

    internal unsafe struct CompressedTexture
    {
        public int ByteLength { get; }
        public byte* Buffer { get; }
    };

    public static class CoolMethods
    {
        public static void Encode(Span<byte> pixels, int width, int height, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
        {
            unsafe
            {
                fixed (byte* pBufer = &MemoryMarshal.GetReference(pixels))
                {
                    var texture = NativeMethods.Encode(pBufer, width, height, mode, mipMapGeneration, quality);

                    // https://github.com/mgravell/Pipelines.Sockets.Unofficial/blob/master/src/Pipelines.Sockets.Unofficial/UnsafeMemory.cs
                    // How to take the byte* into a ReadOnlySpan that is safe?
                    Memory<byte> x;
                    Span<byte> x;

                    StreamWriter writer;
                    

                    NativeMethods.Free(texture.Buffer);
                }
            }
        }
    }
}
