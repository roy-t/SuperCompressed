#pragma once
#include <cstdint>
#include <string>
#include <basisu.h>

namespace basisu
{
	class image;
	struct basis_compressor_params;
}

class NativeEncoder
{
public:
	void Init();
	const basisu::uint8_vec Encode(const std::string& filename, bool uastc, int quality_level, bool perceptual, bool generateMipMaps, bool renormalize);
	void Deinit();
};