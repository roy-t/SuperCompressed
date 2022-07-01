#include "pch.h"

#include "Encoder.h"

using namespace basisu;

CompressedTexture Encode(uint8_t* pImage, int32_t stride, int32_t width, int32_t heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
{	
	image img = image(pImage, width, heigth, 4);

	basis_compressor_params params{};
	params.m_source_images.push_back(img);

	params.m_uastc = true;
	params.m_pack_uastc_flags &= ~cPackUASTCLevelMask;
	static const uint32_t s_level_flags[TOTAL_PACK_UASTC_LEVELS] = { cPackUASTCLevelFastest, cPackUASTCLevelFaster, cPackUASTCLevelDefault, cPackUASTCLevelSlower, cPackUASTCLevelVerySlow };
	params.m_pack_uastc_flags |= s_level_flags[quality];

	switch (mode)
	{
	case Mode::SRgb:
		params.m_perceptual = true;
		params.m_renormalize = false;
		break;
	case Mode::Linear:
		params.m_perceptual = false;		
		params.m_renormalize = false;
		break;
	case Mode::Normalized:
		params.m_perceptual = false;
		params.m_renormalize = true;
		break;
	default:
		break;
	}

	params.m_mip_gen = mipMapGeneration == MipMapGeneration::Full;

	job_pool jpool{ 8 };
	params.m_pJob_pool = &jpool;

	basis_compressor compressor{};

	if (!compressor.init(params))
	{
		//std::string error = fmt::format("Failed to initialize compressor");
		//throw std::exception(error.c_str());

		return { -1, 0, nullptr };		
	}

	auto result = compressor.process();
	if (result != basisu::basis_compressor::cECSuccess)
	{
		//std::string error = fmt::format("Processor failed with {}", result);
		//throw std::exception(error.c_str());

		return { -result, 0, nullptr };
	}

	auto& bytes = compressor.get_output_basis_file();
		
	const CompressedTexture texture = { 64, 16, bytes.data() };
	return texture;
}

void Free(uint8_t* buffer)
{
	free(buffer);
}
