#include "NativeEncoder.h"

#include <basisu_enc.h>
#include <basisu_comp.h>
#include <fmt/format.h>

using namespace basisu;

void NativeEncoder::Init()
{
	// TODO: if multiple instances of this decoder are created they can deinit the library while its used
	basisu_encoder_init();	
}

const uint8_vec NativeEncoder::Encode(const std::string& filename, bool uastc, int quality_level, bool perceptual, bool generateMipMaps, bool renormalize)
{
	image image;
	if (!load_image(filename, image))
	{
		std::string error = fmt::format("Failed to load image {}.", filename);
		throw std::exception(error.c_str());
	}

	basis_compressor_params params{};
	params.m_source_images.push_back(image);

	if (uastc)
	{
		params.m_uastc = true;
		params.m_pack_uastc_flags &= ~cPackUASTCLevelMask;
		static const uint32_t s_level_flags[TOTAL_PACK_UASTC_LEVELS] = { cPackUASTCLevelFastest, cPackUASTCLevelFaster, cPackUASTCLevelDefault, cPackUASTCLevelSlower, cPackUASTCLevelVerySlow };
		params.m_pack_uastc_flags |= s_level_flags[quality_level];
	}
	else
	{
		params.m_uastc = false;
		params.m_quality_level = quality_level;
	}

	params.m_perceptual = perceptual;
	params.m_mip_gen = generateMipMaps;
	params.m_renormalize = renormalize;
	
	job_pool jpool{ 8 };
	params.m_pJob_pool = &jpool;

	basis_compressor compressor{};

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
	basisu_encoder_deinit();
}
