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
    Disabled,
    Enabled,    
};

enum EncodeErrors : int32_t
{
    None,
    FailedInitializing,
    FailedReadingSourceImages,
    FailedValidating,
    FailedEncodeUASTC,
    FailedFrontEnd,
    FailedFontendExtract,
    FailedBackend,
    FailedCreateBasisFile,
    FailedWritingOutput,
    FailedUASTCRDOPostProcess,
    FailedCreateKTX2File,
    OutOfMemory,
};


struct EncodedTexture
{
    EncodeErrors ErrorCode;
    uint8_t* Buffer;
    int32_t Length;
    
};

extern "C"
{   
    _declspec(dllexport) void InitializeEncoder();
    _declspec(dllexport) void DeinitializeEncoder();

    __declspec(dllexport) EncodedTexture Encode(uint8_t* pImage, int32_t components, int32_t width, int32_t heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality);
    __declspec(dllexport) void FreeCompressedTexture(EncodedTexture texture);
}
