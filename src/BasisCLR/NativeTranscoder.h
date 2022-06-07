#pragma once
#include <cstdint>
#include <string>
#include <basisu.h>

class NativeTranscoder
{
public:
	void Init();
	basisu::vector<uint8_t> Transcode(basisu::vector<uint8_t> file, int32_t &width, int32_t &height, int32_t &pitch);
};

