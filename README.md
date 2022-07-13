# SuperCompressed

SuperCompressed is a library for creating 'super compressed' textures from images and transcoding those super compressed textures to common DirectX, OpenGL, and Vulkan [(compressed) pixel formats](http://renderingpipeline.com/2012/07/texture-compression/).

# How does it work?

## Installation
You can install SuperCompressed via the NuGet package manager, or directly via the command line via:

```PS
dotnet add package SuperCompressed
```
> **Warning**
> Because of a native component, SuperCompressed works only on 64bit .NET 6 or higher applications, targetting Windows 7 or higher. In general this is not a problem since you are probably also targetting a native Graphics API if you are using this library.

## Loading an image
SuperCompressed can load any JPG/PNG/TGA/BMP/PSD/GIF image for you. Alternatively you can bring your own image data as a byte array with 1, 2, 3 or 4 color components per pixel.

```C#
using System.IO;
using SuperCompressed;

var image = Image.FromStream(File.OpenRead(filename));

// or alternatively you can provide your own image data
var image = new Image(/*byte[]*/ data, ColorComponents.RedGreenBlue, width, height);
```

## Encoding

You can encode this image using the `Encoder` class. SuperCompressed can work in several different modes, which are useful for different kinds of images.
- `Mode.SRgb`, for regular images, such as photos and diffuse textures
- `Mode.Linear`, for linear data, such as heigth maps and look-up tables
- `Mode.Normalized`, for normalized data, mostly normal maps

There are a few things you can configure:
- [Mipmap](https://en.wikipedia.org/wiki/Mipmap) generation and the filter used to create the mipmaps. See [this](docs/Filters.md) document for an overview of supported filters and their effects.
- Encoding quality settings.

> **Warning**
> Higher quality levels are significantly slower to encode and provide only a fractionally better image quality. In most scenarios the default quality level should suffice.

```C#
Span<byte> encoded = Encoder.Instance.Encode(image, Mode.SRgb, MipMapGeneration.Default /*Kaiser*/, Quality.Default);
```

You can then write the data to disk using the standard .NET APIs.

## Transcoding

When you want to transcode the data to a GPU (compressed) pixel format you can use the `Transcoder` class. You should first query how many images and mipmaps are in the data block that you provided.

> **Note**
> Currently the SuperCompressed Encoder supports only one image per data block. This will change in the future, which is why the Transcoder already has support for multiple images.

```C#
var transcoder = Transcoder.Instance;
var images = transcoder.GetImageCount(encoded);

if (images <= 0)
    return;

var imageIndex = 0;

var levels = transcoder.GetLevelCount(encoded, 0);

if (levels <= 0)
    return;

var mipMapLevel = 0;
```

After you have determined what image and mipmap level you want to transcode. You can do so using the `Transcode` method. Check the [`TranscodeFormats` enum](src/SuperCompressed/TranscodeFormats.cs) for an up to date list of supported formats.


```C#
TranscodedTextureData transcoded = Transcoder.Instance.Transcode(encoded, imageIndex, mipMapLevel, TranscodeFormats.BC7_RGBA);
```
> **Note**
> You will have to call the `Transcode` method multiple times to get all the mipmaps, if there are more than one.


The returned instance of the `TranscodedTextureData` class contains all the information you need to upload the texture to your GPU, using the appropriate method of your graphics framework. For example, using the excellent [Vortice.Windows](https://github.com/amerkoleci/Vortice.Windows) C# bindings for DirectX.

```C#
using Vortice.Direct3D11;
using Vortice.DXGI;

// ....

var description = new Texture2DDescription
{
    Width = transcoded.Width,
    Height = transcoded.Height,
    Format = ToDirectXFormat(transcoded.Format),
    MipLevels = 1,
    ArraySize = 1,
    SampleDescription = new SampleDescription(1, 0),
    Usage = ResourceUsage.Default,
    BindFlags = BindFlags.ShaderResource,
    CPUAccessFlags = CpuAccessFlags.None,
    MiscFlags = ResourceOptionFlags.None
};
ID3D11Texture2D texture = ID3D11Device.CreateTexture2D(description);
ID3D11DeviceContext.UpdateSubresource(transcoded.Data, texture, 0, transcoded.Pitch, 0);
```

After you have uploaded the texture data you should dispose the `TranscodedTextureData` instance to release native memory.

```C#
encoded.Dispose();
```

For more examples checkout the [unit tests](src/SuperCompressed.Tests/UnitTests.cs).

# What is under the hood?

SuperCompressed uses the [Basis Universal](https://github.com/BinomialLLC/basis_universal) GPU Texture Codec for encoding and transcoding textures.
BasisU runs in `UASTC` mode with the RDO optimizations enabled. After encoding the texture is further compressed using the [zstd algorithm](https://github.com/oleg-st/ZstdSharp).

All this leads to files that are frequently less than 20% of the original file size. While also fast to decompress and transcode.

Image | MipMaps | Original size | Encoded size | Compressed size
---|---|---|---|
image_with_alpha.tga | Full | 65536 bytes | 22133 bytes | 15964 bytes |
image_with_alpha.tga | None | 65536 bytes | 16484 bytes | 10737 bytes |


Images are loaded using the [stb-image](https://github.com/StbSharp/StbImageSharp) library.

# Attribution

SuperCompressed builds upon the following libraries
- [Basis Universal](https://github.com/BinomialLLC/basis_universal)
- [ZstdSharp.Port](https://github.com/oleg-st/ZstdSharp)
- [StbImageSharp](https://github.com/StbSharp/StbImageSharp)

The logo used for the NuGet package is [Video Card by Satawat Anukul from NounProject.com](https://thenounproject.com/icon/compress-1644730/)

![Logo Super Compressed](noun-video-card-4546862.png)
