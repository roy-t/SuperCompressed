using StbImageSharp;

namespace SuperCompressed
{
    public enum ColorComponents
    {
        Default,
        Grey,
        GreyAlpha,
        RedGreenBlue,
        RedGreenBlueAlpha
    }

    public sealed class Image
    {
        private readonly byte[] Bytes;

        /// <summary>
        /// Loads a JPG/PNG/BMP/TGA/PSD/GIF as Image using the StbImageSharp library
        /// </summary>
        public static Image FromStream(Stream stream)
        {            
            var image = ImageResult.FromStream(stream);
            return new Image(image.Data, (ColorComponents)image.Comp, image.Width, image.Height);
        }

        /// <summary>
        /// Loads a JPG/PNG/BMP/TGA/PSD/GIF as Image using the StbImageSharp library
        /// </summary>
        public static Image FromMemory(byte[] bytes)
        {
            var image = ImageResult.FromMemory(bytes);
            return new Image(image.Data, (ColorComponents)image.Comp, image.Width, image.Height);
        }

        public Image(byte[] data, ColorComponents components, int width, int height)
        {
            this.Bytes = data;
            Components = components;
            Width = width;
            Height = height;
        }

        public ReadOnlySpan<byte> Data => new ReadOnlySpan<byte>(this.Bytes);
        public ColorComponents Components { get; }

        public int ComponentCount => CountComponents();

        public int Width { get; }
        public int Height { get; }

        private int CountComponents()
        {
            return this.Components switch
            {
                ColorComponents.Grey => 1,
                ColorComponents.GreyAlpha => 2,
                ColorComponents.RedGreenBlue => 3,
                ColorComponents.RedGreenBlueAlpha => 4,
                _ => throw new Exception("Unreachable"),
            };
        }
    }
}