#pragma once

#include <memory>
#include <string>
#include <vector>

class NativeEncoder
{
public:
	void Init();

	const std::vector<uint8_t> Encode(const std::string& filename);
	
	void Deinit();
};