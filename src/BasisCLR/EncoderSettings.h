#pragma once
#include <cstdint>
#include <vector>
#include "Settings.h"

namespace SuperCompressed
{
	namespace BasisUniversal
	{	
        public enum class Ktx2Supercompression : uint32_t
        {
            None = 0,
            BasisLz = 1,
            Standard = 2
        };

        public enum class PackUastcFlags : uint32_t
        {
            // Fastest is the lowest quality, although it's stil substantially higher quality vs. BC1/ETC1. It supports 5 modes.
            // The output may be somewhat blocky because this setting doesn't support 2/3-subset UASTC modes, but it should be less blocky vs. BC1/ETC1.
            // This setting doesn't write BC1 hints, so BC1 transcoding will be slower. 
            // Transcoded ETC1 quality will be lower because it only considers 2 hints out of 32.
            // Avg. 43.45 dB
            LevelFastest = 0,

            // Faster is ~3x slower than fastest. It supports 9 modes.
            // Avg. 46.49 dB
            LEvelFaster = 1,

            // Default is ~5.5x slower than fastest. It supports 14 modes.
            // Avg. 47.47 dB
            LevelDefault = 2,

            // Slower is ~14.5x slower than fastest. It supports all 18 modes.
            // Avg. 48.01 dB
            LevelSlower = 3,

            // VerySlow is ~200x slower than fastest. 
            // The best quality the codec is capable of, but you'll need to be patient or have a lot of cores.
            // Avg. 48.24 dB
            LevelVerySlow = 4,

            LevelMask = 0xF,

            // By default the encoder tries to strike a balance between UASTC and transcoded BC7 quality.
            // These flags allow you to favor only optimizing for lowest UASTC error, or lowest BC7 error.
            FavorUASTCError = 8,
            FavorBC7Error = 16,

            ETC1FasterHints = 64,
            ETC1FastestHints = 128,
            ETC1DisableFlipAndIndividual = 256,

            // Favor UASTC modes 0 and 10 more than the others (this is experimental, it's useful for RDO compression)
            FavorSimplerModes = 512,
        };

		public ref class EncoderSettings
		{
			private:
				array<float>^ settings;

			public:
				EncoderSettings();				
                property bool Uastc;
                property bool YFlip;
                property bool Perceptual;
                property int32_t CompressionLevel;
                property float SelectorRdoThresh;
                property float EndpointRdoThresh;
                property float MipScale;
                property int32_t MipSmallestDimension;
                property uint32_t MaxEndpointClusters;
                property uint32_t MaxSelectorClusters;
                property int32_t QualityLevel;
                property PackUastcFlags PackUastcFlags;
                property float RdoUastcQualityScalar;
                property int32_t RdoUastcDictSize;
                property float RdoUastcMaxSmoothBlockErrorScale;
                property float RdoUastcSmoothBlockMaxStdDev;
                property float RdoUastcMaxAllowedRmsIncreaseRatio;
                property float RdoUastcSkipBlockRmsThresh;
                property int32_t ResampleWidth;
                property int32_t ResampleHeight;
                property float ResampleFactor;
                property Ktx2Supercompression Ktx2UastcSupercompression;
                property int32_t Ktx2ZstdSupercompressionLevel;

			internal:
				void CopyTo(encoder_settings &target);
		};
	}
}
