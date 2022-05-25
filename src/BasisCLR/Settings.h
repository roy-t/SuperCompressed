#pragma once
#include <cstdint>
#include <assert.h>

union FI
{
	float f;
	uint32_t i;	
};

uint32_t reinterpret_as_uint(float value)
{
	assert(sizeof(float) == sizeof(uint32_t));
	union
	{
		float f;
		uint32_t i;
	} u = {value};

	return u.i;
}

int32_t reinterpret_as_int(float value)
{
	assert(sizeof(float) == sizeof(int32_t));
	union
	{
		float f;
		int32_t i;
	} u = { value };

	return u.i;
}

float reinterpret_as_float(uint32_t value)
{
	assert(sizeof(float) == sizeof(uint32_t));
	union
	{
		uint32_t i;
		float f;
	} u = { value };

	return u.f;
}

float reinterpret_as_float(int32_t value)
{
	assert(sizeof(float) == sizeof(int32_t));
	union
	{
		int32_t i;
		float f;
	} u = { value };

	return u.f;
}

enum encoder_settings : uint32_t
{
	compression_level,
	selector_rdo_thresh,
	endpoint_rdo_thresh,
	mip_scale,
	mip_smallest_dimension,
	max_endpoint_clusters,
	max_selector_clusters,
	quality_level,
	pack_uastc_flags,
	rdo_uastc_quality_scalar,
	rdo_uastc_dict_size,
	rdo_uastc_max_smooth_block_error_scale,
	rdo_uastc_smooth_block_max_std_dev,
	rdo_uastc_max_allowed_rms_increase_ratio,
	rdo_uastc_skip_block_rms_thresh,
	resample_width,
	resample_height,
	resample_factor,
	ktx2_uastc_supercompression,
	ktx2_zstd_supercompression_level,
	max_encoder_settings,
};