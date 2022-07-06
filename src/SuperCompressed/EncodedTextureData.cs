namespace SuperCompressed
{
    public sealed unsafe class EncodedTextureData : IDisposable
    {
        private readonly byte* NativeDataPointer;
        private readonly int Length;

        internal unsafe EncodedTextureData(byte* data, int length)
        {
            this.NativeDataPointer = data;
            this.Length = length;
        }

        public Span<byte> Data => new Span<byte>(this.NativeDataPointer, this.Length);

        public void Dispose()
        {
            NativeEncoder.FreeCompressedTexture(this.NativeDataPointer);
        }
    }
}
