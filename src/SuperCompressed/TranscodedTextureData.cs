
namespace SuperCompressed
{
    public unsafe sealed class TranscodedTextureData : IDisposable
    {
        private readonly byte* NativeDataPointer;
        private readonly int Length;

        internal unsafe TranscodedTextureData(byte* data, int length, int width, int height, int pitch, TranscodeFormats format)
        {
            this.NativeDataPointer = data;
            this.Length = length;

            this.Width = width;
            this.Heigth = height;
            this.Pitch = pitch;
            this.Format = format;
        }

        public Span<byte> Data => new Span<byte>(this.NativeDataPointer, this.Length);
        public int Width { get; }
        public int Heigth { get; }
        public int Pitch { get; }
        public TranscodeFormats Format { get; }

        public void Dispose()
        {
            NativeTranscoder.FreeTranscodedTexture(this.NativeDataPointer);
        }
    }
}
