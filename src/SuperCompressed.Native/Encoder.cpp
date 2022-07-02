#include "pch.h"

#include "Encoder.h"

using namespace basisu;

void Initialize()
{
	basisu::basisu_encoder_init();
}

void Deinitialize()
{
	basisu::basisu_encoder_deinit();
}

CompressedTexture Encode(uint8_t* pImage, int32_t components, int32_t width, int32_t heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
{		
	image img = image(pImage, width, heigth, components);

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
		return { basisu::basis_compressor::cECFailedInitializing, 0, nullptr };
	}

	auto result = compressor.process();
	if (result != basisu::basis_compressor::cECSuccess)
	{
		return { result, 0, nullptr };
	}

	auto& data = compressor.get_output_basis_file();
	
	int32_t sizeInBytes = (int32_t)data.size_in_bytes();
	uint8_t* pData = (uint8_t*)malloc(data.size_in_bytes());	

	if (pData == nullptr)
	{
		return { -1 , 0, nullptr };
	}
	else
	{
		memcpy(pData, data.get_ptr(), data.size_in_bytes());
	}

	return { 0, sizeInBytes, pData};
}

void Free(uint8_t* buffer)
{
	free(buffer);
}
