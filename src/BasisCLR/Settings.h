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

struct encoder_settings
{
	bool uastc;
	bool y_flip;
	bool perceptual;
	int32_t compression_level;
	float selector_rdo_thresh;
	float endpoint_rdo_thresh;
	float mip_scale;
	int32_t mip_smallest_dimension;
	uint32_t max_endpoint_clusters;
	uint32_t max_selector_clusters;
	int32_t quality_level;
	uint32_t pack_uastc_flags;
	float rdo_uastc_quality_scalar;
	int32_t rdo_uastc_dict_size;
	float rdo_uastc_max_smooth_block_error_scale;
	float rdo_uastc_smooth_block_max_std_dev;
	float rdo_uastc_max_allowed_rms_increase_ratio;
	float rdo_uastc_skip_block_rms_thresh;
	int32_t resample_width;
	int32_t resample_height;
	float resample_factor;
	uint32_t ktx2_uastc_supercompression;
	int32_t ktx2_zstd_supercompression_level;
};