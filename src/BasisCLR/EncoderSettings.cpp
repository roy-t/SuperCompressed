#include "EncoderSettings.h"
#include "Settings.h"

SuperCompressed::BasisUniversal::EncoderSettings::EncoderSettings()
{	
	Uastc = false;
	YFlip = false;
	Perceptual = true;
	CompressionLevel = 2u;
	SelectorRdoThresh = 1.25f;
	EndpointRdoThresh = 1.5f;
	MipScale = 1.0f;
	MipSmallestDimension = 1;
	MaxEndpointClusters = 512;
	MaxSelectorClusters = 512;
	QualityLevel = -1;
	PackUastcFlags = SuperCompressed::BasisUniversal::PackUastcFlags::LevelDefault;
	RdoUastcQualityScalar = 1.0f;
	RdoUastcDictSize = 4096;
	RdoUastcMaxSmoothBlockErrorScale = 10.0f;
	RdoUastcSmoothBlockMaxStdDev = 18.0f;
	RdoUastcMaxAllowedRmsIncreaseRatio = 10.0f;
	RdoUastcSkipBlockRmsThresh = 8.0f;
	ResampleWidth = 0;
	ResampleHeight = 0;
	ResampleFactor = 0.0f;
	Ktx2UastcSupercompression = SuperCompressed::BasisUniversal::Ktx2Supercompression::None;
	Ktx2ZstdSupercompressionLevel = 6;
}

void SuperCompressed::BasisUniversal::EncoderSettings::CopyTo(encoder_settings &target)
{	
	target.uastc = Uastc;
	target.y_flip = YFlip;
	target.perceptual = Perceptual;
	target.compression_level = CompressionLevel;
	target.selector_rdo_thresh = SelectorRdoThresh;
	target.endpoint_rdo_thresh = EndpointRdoThresh;
	target.mip_scale = MipScale;
	target.mip_smallest_dimension = MipSmallestDimension;
	target.max_endpoint_clusters = MaxEndpointClusters;
	target.max_selector_clusters = MaxSelectorClusters;
	target.quality_level = QualityLevel;
	target.pack_uastc_flags = (uint32_t)PackUastcFlags;
	target.rdo_uastc_quality_scalar = RdoUastcQualityScalar;
	target.rdo_uastc_dict_size = RdoUastcDictSize;
	target.rdo_uastc_max_smooth_block_error_scale = RdoUastcMaxSmoothBlockErrorScale;
	target.rdo_uastc_smooth_block_max_std_dev = RdoUastcSmoothBlockMaxStdDev;
	target.rdo_uastc_max_allowed_rms_increase_ratio = RdoUastcMaxAllowedRmsIncreaseRatio;
	target.rdo_uastc_skip_block_rms_thresh = RdoUastcSkipBlockRmsThresh;
	target.resample_width = ResampleWidth;
	target.resample_height = ResampleHeight;
	target.resample_factor = ResampleFactor;
	target.ktx2_uastc_supercompression = (uint32_t)Ktx2UastcSupercompression;
	target.ktx2_zstd_supercompression_level = Ktx2ZstdSupercompressionLevel;
}
