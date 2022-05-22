#include "Encoder.h"
#include "NativeEncoder.h"

#include <string>
#include <assert.h>
#include <msclr\marshal_cppstd.h>

using namespace System;

SuperCompressed::BasisUniversal::Encoder::Encoder()
{
	this->encoder = new NativeEncoder();
	this->encoder->Init();	
}

SuperCompressed::BasisUniversal::Encoder::~Encoder()
{
	if (this->encoder != nullptr)
	{
		this->encoder->Deinit();
		delete this->encoder;
		this->encoder = nullptr;
	}
}

array<Byte>^ SuperCompressed::BasisUniversal::Encoder::Encode(array<uint8_t>^ data, uint32_t width, uint32_t height, String^ name)
{
	auto nameC = msclr::interop::marshal_as<std::string>(name);

	try
	{
		auto size = sizeof(uint8_t) * data->Length;		
		uint8_t *pImage = (uint8_t *)malloc(size);		
		pin_ptr<uint8_t> pData = &data[0];
		
		memcpy_s(pImage, size, pData, size);
		
		auto output = this->encoder->Encode(pImage, width, height, nameC);
		return CreateManagedBuffer(output);
	}
	catch (std::exception& exception)
	{
		auto message = gcnew String(exception.what());
		throw gcnew Exception(message);
	}
}

array<Byte>^ SuperCompressed::BasisUniversal::Encoder::Encode(String^ filename)
{
	assert(this->encoder != nullptr);

	auto filenameC = msclr::interop::marshal_as<std::string>(filename);

	try
	{		
		auto output = this->encoder->Encode(filenameC);
		return CreateManagedBuffer(output);
	}
	catch (std::exception& exception)
	{
		auto message = gcnew String(exception.what());
		throw gcnew Exception(message);
	}	
}

inline array<Byte>^ SuperCompressed::BasisUniversal::Encoder::CreateManagedBuffer(basisu::uint8_vec output)
{
	auto buffer = gcnew array<Byte>((int)output.size());
	pin_ptr<Byte> bufferStart = &buffer[0];
	memcpy_s(bufferStart, buffer->Length, &output[0], output.size());

	return buffer;
}
