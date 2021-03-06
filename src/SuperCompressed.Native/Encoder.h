#pragma once

#include <stdint.h>

extern "C"
{   
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
        MMG_Default,
        Box,
        Tent,
        Bell,
        BSpline,
        Mitchell,
        Blackman,
        Lanczos3,
        Lanczos4,
        Lanczos6,
        Lanczos12,
        Kaiser,
        Gaussian,
        Catmullrom,
        QuadraticInterpolation,
        QuadraticApproximation,
        QuadraticMix
    };

    enum EncodeErrors : uint8_t
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

    _declspec(dllexport) void InitializeEncoder();
    _declspec(dllexport) void DeinitializeEncoder();

    __declspec(dllexport) EncodedTexture Encode(uint8_t* pImage, int32_t components, int32_t width, int32_t heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality);
    __declspec(dllexport) void FreeCompressedTexture(uint8_t* texture);
}
