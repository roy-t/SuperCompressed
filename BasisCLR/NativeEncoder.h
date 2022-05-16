#pragma once

#include <string>

class NativeEncoder
{
public:
	void Init();

	void Encode(const std::string& filename);
	
	void Deinit();

};