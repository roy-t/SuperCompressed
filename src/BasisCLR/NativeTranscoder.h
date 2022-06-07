#pragma once
#include <cstdint>
#include <string>
#include <basisu.h>

class NativeTranscoder
{
public:
	void Init();

	uint32_t GetImageCount(basisu::vector<uint8_t> file);
	uint32_t GetMipMapCount(basisu::vector<uint8_t> file, uint32_t image);
	basisu::vector<uint8_t> Transcode(basisu::vector<uint8_t> file, uint32_t image, uint32_t mipmap, int32_t &width, int32_t &height, int32_t &pitch);
};

