using System.Runtime.InteropServices;

namespace SuperCompressed
{
    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct CompressedTexture
    {
        public int ErrorCode { get; }
        public int SizeInBytes { get; }
        public byte* Buffer { get; }
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
}
