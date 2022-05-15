# SuperCompressedDotNet
A .NET wrapper for BinomialLLC's Basis Universal Supercompressed GPU Texture Codec. Which is located here: https://github.com/BinomialLLC/basis_universal.

The goal of this project is to provide a single NuGet packages that allows x64 C# projects to use the Basis Universal encoder and transcoder.

Very much a work-in-progress. 

## Notes
The original source code is includes as a git submodule in /external/basisu_universal, but a few small changes have been made that I would prefer to make externally
- Compilation was changed from an .exe to a .lib

The VCPKG approach would have been the preferred approach, but unfortunately the basis version on vcpkg is quite a bit older and lacks big features (for example, OpenCL support).



## Reading List
http://renderingpipeline.com/2012/07/texture-compression/