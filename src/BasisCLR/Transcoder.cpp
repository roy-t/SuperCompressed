#include "Transcoder.h"
#include "NativeTranscoder.h"

#include <string>
#include <assert.h>
#include <msclr\marshal_cppstd.h>

using namespace System;

SuperCompressed::BasisUniversal::Transcoder::Transcoder()
{
	transcoder = new NativeTranscoder();
	transcoder->Init();
}

SuperCompressed::BasisUniversal::Transcoder::~Transcoder()
{
	if (transcoder != nullptr)
	{
		delete transcoder;
		transcoder = nullptr;
	}
}

int32_t SuperCompressed::BasisUniversal::Transcoder::GetImageCount(array<uint8_t>^ data)
{
	try
	{
		pin_ptr<uint8_t> pData = &data[0];

		basisu::vector<uint8_t> file;
		file.append(pData, data->Length);
		return transcoder->GetImageCount(file);
	}
	catch (std::exception& exception)
	{
		auto message = gcnew String(exception.what());
		throw gcnew Exception(message);
	}
}

int32_t SuperCompressed::BasisUniversal::Transcoder::GetMipMapCount(array<uint8_t>^ data, int32_t image)
{
	try
	{
		pin_ptr<uint8_t> pData = &data[0];

		basisu::vector<uint8_t> file;
		file.append(pData, data->Length);
		return transcoder->GetMipMapCount(file, image);
	}
	catch (std::exception& exception)
	{
		auto message = gcnew String(exception.what());
		throw gcnew Exception(message);
	}
}

array<Byte>^ SuperCompressed::BasisUniversal::Transcoder::Transcode(array<uint8_t>^ data, int32_t image, int32_t mipmap, int32_t% width, int32_t% height, int32_t% pitch)
{	
	try
	{
		pin_ptr<uint8_t> pData = &data[0];

		basisu::vector<uint8_t> file;
		file.append(pData, data->Length);

		int32_t cWidth = 0;
		int32_t cHeigth = 0;
		int32_t cPitch = 0;
		auto output = transcoder->Transcode(file, image, mipmap, cWidth, cHeigth, cPitch);
		
		width = cWidth;
		height = cHeigth;
		pitch = cPitch;

		return ConvertToManagedBuffer(output);
	}
	catch (std::exception& exception)
	{
		auto message = gcnew String(exception.what());
		throw gcnew Exception(message);
	}
}

inline array<Byte>^ SuperCompressed::BasisUniversal::Transcoder::ConvertToManagedBuffer(basisu::uint8_vec output)
{
	auto buffer = gcnew array<Byte>((int)output.size());
	pin_ptr<Byte> bufferStart = &buffer[0];
	memcpy_s(bufferStart, buffer->Length, &output[0], output.size());

	output.clear();

	return buffer;
}
