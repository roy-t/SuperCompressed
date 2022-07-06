namespace SuperCompressed
{
    // NOTE: Formats that are commented out are supported by BasisU, but did not work when I tested them on Windows
    // using an NVidia RTX2080. These formats are either extremely niche or intended for mobile devices

    public enum TranscodeFormats : byte
    {
        // ETC1-2

        /// <summary>
        /// Opaque only, returns RGB or alpha data if cDecodeFlagsTranscodeAlphaDataToOpaqueFormats flag is specified
        /// </summary>
        ETC1_RGB = 0,
        /// <summary>
        /// Opaque+alpha, ETC2_EAC_A8 block followed by a ETC1 block, alpha channel will be opaque for opaque .basis files
        /// </summary>
        ETC2_RGBA = 1,

        // BC1-5, BC7 (desktop, some mobile devices)

        /// <summary>
        /// Opaque only, no punchthrough alpha support yet, transcodes alpha slice if cDecodeFlagsTranscodeAlphaDataToOpaqueFormats flag is specified
        /// </summary>
        BC1_RGB = 2,
        /// <summary>
        /// Opaque+alpha, BC4 followed by a BC1 block, alpha channel will be opaque for opaque .basis files
        /// </summary>
        BC3_RGBA = 3,
        /// <summary>
        /// Red only, alpha slice is transcoded to output if cDecodeFlagsTranscodeAlphaDataToOpaqueFormats flag is specified
        /// </summary>
        BC4_R = 4,
        /// <summary>
        /// XY: Two BC4 blocks, X=R and Y=Alpha, .basis file should have alpha data (if not Y will be all 255's)
        /// </summary>
        BC5_RG = 5,
        /// <summary>
        /// RGB or RGBA, mode 5 for ETC1S, modes (1,2,3,5,6,7) for UASTC
        /// </summary>
        BC7_RGBA = 6,

        // PVRTC1 4bpp (mobile, PowerVR devices)

        /// <summary>
        /// Opaque only, RGB or alpha if cDecodeFlagsTranscodeAlphaDataToOpaqueFormats flag is specified, nearly lowest quality of any texture format.
        /// </summary>
        PVRTC1_4_RGB = 8,
        /// <summary>
        /// Opaque+alpha, most useful for simple opacity maps. If .basis file doesn't have alpha PVRTC1_4_RGB will be used instead. Lowest quality of any supported texture format.
        /// </summary>
        PVRTC1_4_RGBA = 9,

        // ASTC (mobile, Intel devices, hopefully all desktop GPU's one day)

        /// <summary>
        /// Opaque+alpha, ASTC 4x4, alpha channel will be opaque for opaque .basis files. Transcoder uses RGB/RGBA/L/LA modes, void extent, and up to two ([0,47] and [0,255]) endpoint precisions.
        /// </summary>
        ASTC_4x4_RGBA = 10,

        //// ATC (mobile, Adreno devices, this is a niche format)

        ///// <summary>
        ///// Opaque, RGB or alpha if cDecodeFlagsTranscodeAlphaDataToOpaqueFormats flag is specified. ATI ATC (GL_ATC_RGB_AMD)
        ///// </summary>
        //ATC_RGB = 11,
        ///// <summary>
        ///// Opaque+alpha, alpha channel will be opaque for opaque .basis files. ATI ATC (GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD) 
        ///// </summary>
        //ATC_RGBA = 12,

        //// FXT1 (desktop, Intel devices, this is a super obscure format)

        ///// <summary>
        ///// Opaque only, uses exclusively CC_MIXED blocks. Notable for having a 8x4 block size. GL_3DFX_texture_compression_FXT1 is supported on Intel integrated GPU's (such as HD 630).
        ///// Punch-through alpha is relatively easy to support, but full alpha is harder. This format is only here for completeness so opaque-only is fine for now.
        ///// See the BASISU_USE_ORIGINAL_3DFX_FXT1_ENCODING macro in basisu_transcoder_internal.h.
        ///// </summary>
        //FXT1_RGB = 17,

        ///// <summary>
        ///// Opaque-only, almost BC1 quality, much faster to transcode and supports arbitrary texture dimensions (unlike PVRTC1 RGB).
        ///// </summary>
        //PVRTC2_4_RGB = 18,
        ///// <summary>
        ///// Opaque+alpha, slower to encode than PVRTC2_4_RGB. Premultiplied alpha is highly recommended, otherwise the color channel can leak into the alpha channel on transparent blocks.
        ///// </summary>
        //PVRTC2_4_RGBA = 19,

        /// <summary>
        /// R only (ETC2 EAC R11 unsigned)
        /// </summary>
        ETC2_EAC_R11 = 20,
        /// <summary>
        /// RG only (ETC2 EAC RG11 unsigned), R=opaque.r, G=alpha - for tangent space normal maps
        /// </summary>
        ETC2_EAC_RG11 = 21,

        // Uncompressed (raw pixel) formats
        /// <summary>
        /// 32bpp RGBA image stored in raster (not block) order in memory, R is first byte, A is last byte.
        /// </summary>
        RGBA32 = 13,
        /// <summary>
        /// 16bpp RGB image stored in raster (not block) order in memory, R at bit position 11
        /// </summary>
        RGB565 = 14,
        /// <summary>
        /// 16bpp RGB image stored in raster (not block) order in memory, R at bit position 0
        /// </summary>
        BGR565 = 15,
        /// <summary>
        /// 16bpp RGBA image stored in raster (not block) order in memory, R at bit position 12, A at bit position 0
        /// </summary>
        RGBA4444 = 16,
    };
}
