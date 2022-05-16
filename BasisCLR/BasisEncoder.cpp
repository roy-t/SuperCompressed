#include "pch.h"
#include "Encoder.h"

#include "BasisEncoder.h"

SuperCompressed::BasisUniversal::BasisEncoder::BasisEncoder()
{
	this->encoder = new Encoder();
	this->encoder->Init();	
}

SuperCompressed::BasisUniversal::BasisEncoder::~BasisEncoder()
{
	if (this->encoder != nullptr)
	{
		this->encoder->Deinit();
		this->encoder = nullptr;
	}
}
