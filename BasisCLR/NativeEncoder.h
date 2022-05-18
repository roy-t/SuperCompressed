#pragma once

#include <memory>
#include <string>
#include <vector>
#include <basisu.h>

class NativeEncoder
{
public:
	void Init();

	const basisu::uint8_vec Encode(const std::string& filename);
	
	void Deinit();
};