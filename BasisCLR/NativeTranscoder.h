#pragma once
#include <cstdint>
#include <string>
#include <basisu.h>

class NativeTranscoder
{
public:
	void Init();
	basisu::vector<uint8_t> Transcode(basisu::vector<uint8_t> file, std::string name);
};

