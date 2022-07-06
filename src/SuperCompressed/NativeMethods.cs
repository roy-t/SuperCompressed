using System.Runtime.InteropServices;

namespace SuperCompressed
{
    internal enum EncodeErrors : byte
    {
        None,
        FailedInitializing,
        FailedReadingSourceImages,
        FailedValidating,
        FailedEncodeUASTC,
        FailedFrontEnd,
        FailedFontendExtract,
        FailedBackend,
        FailedCreateBasisFile,
        FailedWritingOutput,
        FailedUASTCRDOPostProcess,
        FailedCreateKTX2File,
        OutOfMemory,
    };

    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct EncodedTexture
    {
        public EncodeErrors ErrorCode { get; }        
        public byte* Buffer { get; }
        public int Length { get; }
    };

    internal static class NativeEncoder
    {
        [DllImport("SuperCompressed.Native.dll", EntryPoint = "InitializeEncoder")]
        public static extern void InitializeEncoder();

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "DeinitializeEncoder")]
        public static extern void DeinitializeEncoder();

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "InitializeTranscoder")]
        public static extern void InitializeTranscoder();

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "DeinitializeTranscoder")]
        public static extern void DeinitializeTranscoder();

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "Encode")]
        public static unsafe extern EncodedTexture Encode(byte* buffer, int components, int width, int heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality);

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "FreeCompressedTexture")]
        public static unsafe extern void FreeCompressedTexture(byte* texture);
    }


    internal enum TranscodeErrors : byte
    {
        None,
        InvalidHeader,
        InvalidFileInfo,
        InvalidImageInfo,
        InvalidImageLevelDescription,
        ImageIndexOutOfRange,
        LevelIndexOutOfRange,
        Failed,
        OutOfMemory,
    };


    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct TranscodedTexture
    {
        public TranscodeErrors ErrorCode { get; }
        public byte* Buffer { get; }
        public int Length { get; }
        public int Width { get; }
        public int Heigth { get; }
        public int Pitch { get; }
    };

    internal static class NativeTranscoder
    {
        [DllImport("SuperCompressed.Native.dll", EntryPoint = "InitializeTranscoder")]
        public static extern void InitializeTranscoder();

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "GetImageCount")]
        public static unsafe extern int GetImageCount(byte* buffer, int length);

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "GetLevelCount")]
        public static unsafe extern int GetLevelCount(byte* buffer, int length, int imageIndex);

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "Transcode")]
        public static unsafe extern TranscodedTexture Transcode(byte* buffer, int length, int imageIndex, int levelIndex, TranscodeFormats targetFormat);

        [DllImport("SuperCompressed.Native.dll", EntryPoint = "FreeTranscodedTexture")]
        public static unsafe extern void FreeTranscodedTexture(byte* texture);
    }
}
