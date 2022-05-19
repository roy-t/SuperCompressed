#pragma once

#include <memory>
#include <string>
#include <vector>
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

	const basisu::uint8_vec Encode(const std::string& filename);
	const basisu::uint8_vec Encode(uint8_t* data, uint32_t width, uint32_t height, const std::string& name);

	void Deinit();

private:
	const basisu::uint8_vec Encode(const basisu::image& image, const std::string& name);
		
	
};