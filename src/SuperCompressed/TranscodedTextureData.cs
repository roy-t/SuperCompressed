namespace SuperCompressed
{
    public sealed class TranscodedTextureData
    {
        internal unsafe TranscodedTextureData(byte* data, int length, int width, int height, int pitch, TranscodeFormats format)
        {
            this.Data = new byte[length];

            var span = new ReadOnlySpan<byte>(data, length);
            span.CopyTo(this.Data);
                        
            this.Width = width;
            this.Heigth = height;
            this.Pitch = pitch;
            this.Format = format;
        }

        public byte[] Data { get; }
        public int Width { get; }
        public int Heigth { get; }
        public int Pitch { get; }
        public TranscodeFormats Format { get; }
    }
}
