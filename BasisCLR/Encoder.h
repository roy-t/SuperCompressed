#pragma once

#include <string>

class Encoder
{
public:
	void Init();

	void Encode(const std::string& filename);
	
	void Deinit();

};