#include "NativeEncoder.h"

#include <basisu_enc.h>
#include <basisu_comp.h>
#include <fmt/format.h>

using namespace basisu;

void NativeEncoder::Init()
{
	basisu_encoder_init();
}

const uint8_vec NativeEncoder::Encode(const std::string &filename)
{
	image image;
	if (!load_image(filename, image))
	{
		std::string error = fmt::format("Failed to load image {}.", filename);		
		throw std::exception(error.c_str());
	}

	basis_compressor_params params;
	params.m_source_images.push_back(image);
	params.m_perceptual = true;
	params.m_check_for_alpha = true;
	params.m_uastc = true;
	params.m_write_output_basis_files = false;

	job_pool jpool(1);
	params.m_pJob_pool = &jpool;

	basis_compressor compressor;
	
	if (!compressor.init(params))
	{
		std::string error = fmt::format("Failed to initialize compressor for image {}", filename);
		throw std::exception(error.c_str());
	}

	auto result = compressor.process();
	if (result != basisu::basis_compressor::cECSuccess)
	{
		std::string error = fmt::format("Processor failed with {} for image {}", result, filename);
		throw std::exception(error.c_str());
	}

	return compressor.get_output_basis_file();
}

void NativeEncoder::Deinit()
{
	basisu::basisu_encoder_deinit();
}
