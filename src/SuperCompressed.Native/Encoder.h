#pragma once

#include "pch.h"

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
    int ByteLength;
    uint8_t* Buffer;
};

extern "C"
{    
    __declspec(dllexport) CompressedTexture Encode(uint8_t* buffer, int32_t width, int32_t heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality);
    __declspec(dllexport) void Free(uint8_t* buffer);
}
