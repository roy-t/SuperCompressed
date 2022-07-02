#pragma once

#include <stdint.h>

enum Quality : uint8_t 
{
    Fastest,
    Faster,
    Default,
    Slower,
    Slowest
};

enum Mode : uint8_t
{
    SRgb,
    Linear,    
    Normalized        
};

enum MipMapGeneration : uint8_t
{
    None,
    Full,    
};


struct CompressedTexture
{
    int32_t ErrorCode;
    int32_t SizeInBytes;
    const uint8_t* Buffer;
};

extern "C"
{   
    _declspec(dllexport) void Initialize();
    _declspec(dllexport) void Deinitialize();

    __declspec(dllexport) CompressedTexture Encode(uint8_t* pImage, int32_t components, int32_t width, int32_t heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality);
    __declspec(dllexport) void Free(uint8_t* buffer);
}
