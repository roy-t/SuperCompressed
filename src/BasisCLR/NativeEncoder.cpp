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

	return Encode(image, filename);
}

const basisu::uint8_vec NativeEncoder::Encode(uint8_t* pImage, uint32_t width, uint32_t height, const std::string& name)
{
	image foo = image(width, height);
	foo.grant_ownership(reinterpret_cast<color_rgba*>(pImage), width, height);

	return Encode(foo, name);
}

const uint8_vec NativeEncoder::Encode(const image& image, const std::string &name)
{
	basis_compressor_params params{};
	params.m_source_images.push_back(image);
	params.m_uastc = false;
	params.m_quality_level = 128;

	job_pool jpool{ 8 };
	params.m_pJob_pool = &jpool;

	basis_compressor compressor{};

	if (!compressor.init(params))
	{
		std::string error = fmt::format("Failed to initialize compressor for image {}", name);
		throw std::exception(error.c_str());
	}

	auto result = compressor.process();
	if (result != basisu::basis_compressor::cECSuccess)
	{
		std::string error = fmt::format("Processor failed with {} for image {}", result, name);
		throw std::exception(error.c_str());
	}

	return compressor.get_output_basis_file();
}

void NativeEncoder::Deinit()
{
	basisu::basisu_encoder_deinit();
}
