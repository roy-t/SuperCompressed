using System.Buffers;
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
        public static unsafe extern CompressedTexture Encode(byte* buffer, int stride, int width, int heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality);

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "Free")]
        public static unsafe extern void Free(byte* buffer);
    }

    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct CompressedTexture
    {
        public int Stride { get; }
        public int ByteLength { get; }
        public byte* Buffer { get; }
    };

    public unsafe sealed class Texture : IDisposable
    {
        private readonly bool IsUnmanagedMemory;
        private readonly MemoryHandle Handle;

        public static Texture TakeOwnerShipOfNativePointer(byte* pixels, int stride, int width, int height)
        {
            return new Texture(pixels, stride, width, height);
        }

        private unsafe Texture(byte* pixels, int stride, int width, int height)
        {
            this.Handle = new MemoryHandle(pixels);            
            this.Stride = stride;
            this.Width = width;
            this.Height = height;

            this.IsUnmanagedMemory = true;
        }

        public Texture(Memory<byte> pixels, int stride, int width, int height)
        {
            this.Handle = pixels.Pin();
            this.Stride = stride;
            this.Width = width;
            this.Height = height;

            this.IsUnmanagedMemory = false;
        }

        public Span<byte> GetSpan()
        {
            return new Span<byte>(this.Handle.Pointer, this.Stride * this.Height);
        }

        internal byte* Pointer => (byte*)this.Handle.Pointer;

        public int Stride { get; }
        public int Width { get; }
        public int Height { get; }

        public void Dispose()
        {
            if (this.IsUnmanagedMemory && this.Handle.Pointer != null)
            {
                NativeMethods.Free((byte*)this.Handle.Pointer);
            }
            this.Handle.Dispose();
        }
    }

    public static class CoolMethods
    {
        public static Texture Encode(Texture texture, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
        {
            unsafe
            {
                var compressed = NativeMethods.Encode(texture.Pointer, texture.Stride, texture.Width, texture.Height, mode, mipMapGeneration, quality);
                return Texture.TakeOwnerShipOfNativePointer(compressed.Buffer, compressed.Stride, texture.Width, texture.Height);
            }

        }      
    }
}
