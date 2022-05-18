#pragma once

#include <memory>
#include <string>
#include <vector>
#include <basisu.h>

namespace basisu
{
	class image;
}

class NativeEncoderSettings
{
public:
	uint32_t m_threads;
	bool m_perceptual;
	bool m_alpha;
	bool m_uastc;
	bool m_mipmap;
};

class NativeEncoder
{
public:
	void Init();

	const basisu::uint8_vec Encode(const std::string& filename, const NativeEncoderSettings settings);
	const basisu::uint8_vec Encode(uint8_t* data, uint32_t width, uint32_t height, const NativeEncoderSettings settings, const std::string& name);

	void Deinit();

private:
	const basisu::uint8_vec Encode(const basisu::image& image, const NativeEncoderSettings settings, const std::string& name);
		
	
};