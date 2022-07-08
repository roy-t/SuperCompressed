# SuperCompressed

SuperCompressed is a library that allows you to create, and work with, [compressed texture formats](http://renderingpipeline.com/2012/07/texture-compression/) in your game and multimedia applications. It uses Binomial's [Basis Universal Supercompressed GPU Texture Codec](https://github.com/BinomialLLC/basis_universal).

Using SuperCompressed you can compress your images to the intermediate .basis format. This format can be quickly transcoded to a wide variety of GPU compressed and uncompressed pixel formats. From ASTC and BC1~7 to ETC and PVRTC. For a complete list see [TranscodeFormats.cs](src/SuperCompressed/TranscodeFormats.cs). 

This library contains both the encoding and transcoding parts. Great for use in your asset pipeline, game engine, or other multimedia project.


## Installation
Because of native components you can only use SuperCompressed in projets targetting `.NET 6.0` on Windows, 64 bits. 


# Notes
SuperCompressed uses Basis Universal's `UASTC`-mode. Which is the high-quality mode and is suitable for all texture types, including normal maps. Using Basis Universal's RDO optimization and further losless compression using the `Brotli` algorithm the image is super compressed.

Image | Original Size| Encoded Size | Supercompressed Size
---|---|---|---|
image_with_alpha.tga | 65536 bytes | 22133 bytes | 14735 bytes |
					 || 100% | 34 % | 22% |




## Support
SuperCompressed only supports projects that target .NET 6 and higher 

The goal of this project is to provide a single NuGet packages that allows x64 C# projects to use the Basis Universal encoder and transcoder.

Very much a work-in-progress. 



## Notes
When pulling the latest version of Basis Universal in the `src/external/basis_universal` submodule folder. Make sure to double check any new/renamed/removed files are present in `src/external/basisu_lib.vcxproj`

## Reading List
http://renderingpipeline.com/2012/07/texture-compression/



![Logo Super Compressed](noun-video-card-4546862.png)

*Logo: [Video Card by Satawat Anukul from NounProject.com](https://thenounproject.com/icon/compress-1644730/)*


