#include "pch.h"
#include "Encoder.h"

using namespace basisu;

void InitializeEncoder()
{
	basisu::basisu_encoder_init();
}

void DeinitializeEncoder()
{
	basisu::basisu_encoder_deinit();
}

EncodedTexture Encode(uint8_t* pImage, int32_t components, int32_t width, int32_t heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
{		
	image img = image(pImage, width, heigth, components);

	basis_compressor_params params{};
	params.m_source_images.push_back(img);

	params.m_uastc = true;
	params.m_rdo_uastc = true;
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

	params.m_mip_gen = mipMapGeneration != MipMapGeneration::Disabled;
	if (mipMapGeneration == MipMapGeneration::Box) { params.m_mip_filter = "box"; }
	if (mipMapGeneration == MipMapGeneration::Tent) { params.m_mip_filter = "tent"; }
	if (mipMapGeneration == MipMapGeneration::Bell) { params.m_mip_filter = "bell"; }
	if (mipMapGeneration == MipMapGeneration::BSpline) { params.m_mip_filter = "b-spline"; }
	if (mipMapGeneration == MipMapGeneration::Mitchell) { params.m_mip_filter = "mitchell"; }
	if (mipMapGeneration == MipMapGeneration::Blackman) { params.m_mip_filter = "blackman"; }
	if (mipMapGeneration == MipMapGeneration::Lanczos3) { params.m_mip_filter = "lanczos3"; }
	if (mipMapGeneration == MipMapGeneration::Lanczos4) { params.m_mip_filter = "lanczos4"; }
	if (mipMapGeneration == MipMapGeneration::Lanczos6) { params.m_mip_filter = "lanczos6"; }
	if (mipMapGeneration == MipMapGeneration::Lanczos12) { params.m_mip_filter = "lanczos12"; }
	if (mipMapGeneration == MipMapGeneration::Kaiser) { params.m_mip_filter = "kaiser"; }
	if (mipMapGeneration == MipMapGeneration::Gaussian) { params.m_mip_filter = "gaussian"; }
	if (mipMapGeneration == MipMapGeneration::Catmullrom) { params.m_mip_filter = "catmullrom"; }
	if (mipMapGeneration == MipMapGeneration::QuadraticInterpolation) { params.m_mip_filter = "quadratic_interp"; }
	if (mipMapGeneration == MipMapGeneration::QuadraticApproximation) { params.m_mip_filter = "quadratic_approx"; }
	if (mipMapGeneration == MipMapGeneration::QuadraticMix) { params.m_mip_filter = "quadratic_mix"; }

	if (mipMapGeneration == MipMapGeneration::MMG_Default) { params.m_mip_filter = "kaiser"; }

	job_pool jpool{ 8 };
	params.m_pJob_pool = &jpool;

	basis_compressor compressor{};

	if (!compressor.init(params))
	{		
		return { EncodeErrors::FailedInitializing, nullptr, 0};
	}

	auto result = compressor.process();
	if (result != basisu::basis_compressor::cECSuccess)
	{
		return { (EncodeErrors)result, nullptr, 0 };
	}

	auto& data = compressor.get_output_basis_file();
		
	uint8_t* pData = (uint8_t*)malloc(data.size_in_bytes());	

	if (pData == nullptr)
	{
		return { EncodeErrors::OutOfMemory , nullptr, 0 };
	}
	else
	{
		memcpy(pData, data.get_ptr(), data.size_in_bytes());
	}

	return { EncodeErrors::None, pData, (int32_t)data.size_in_bytes() };
}

void FreeCompressedTexture(uint8_t* texture)
{
	free(texture);
}
