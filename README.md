# SuperCompressed

SuperCompressed is a library that allows you to create, and work with, compressed texture formats in your game and multimedia applications. It uses Binomial's [Basis Universal Supercompressed GPU Texture Codec](https://github.com/BinomialLLC/basis_universal).

Using SuperCompressed you can compress your images to the intermediate .basis format. This format can be quickly transcoded to a wide variety of GPU compressed and uncompressed pixel formats. From ASTC and BC1~7 to ETC and PVRTC. For a complete list see [TranscodeFormats.cs](src/SuperCompressed/TranscodeFormats.cs). 


# Notes
SuperCompressed uses Basis Universal's `UASTC`-mode. Which is the high-quality mode and is suitable for all texture types, including normal maps. Compressed files are stream 


## Support
SuperCompressed only supports projects that target .NET 6 and higher 

The goal of this project is to provide a single NuGet packages that allows x64 C# projects to use the Basis Universal encoder and transcoder.

Very much a work-in-progress. 



## Notes
When pulling the latest version of Basis Universal in the `src/external/basis_universal` submodule folder. Make sure to double check any new/renamed/removed files are present in `src/external/basisu_lib.vcxproj`

## Reading List
http://renderingpipeline.com/2012/07/texture-compression/





![Logo Super Compressed](noun-video-card-4546862.png)

Logo: [Video Card by Satawat Anukul from NounProject.com](https://thenounproject.com/icon/compress-1644730/)
