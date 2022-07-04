namespace SuperCompressed
{
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
}
