namespace SuperCompressed
{
    public sealed class EncodedTextureData
    {
        internal unsafe EncodedTextureData(byte* data, int length)
        {
            this.Data = new byte[length];

            var span = new ReadOnlySpan<byte>(data, length);
            span.CopyTo(this.Data);
        }

        public byte[] Data { get; }
    }
}
