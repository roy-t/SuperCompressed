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

array<Byte>^ SuperCompressed::BasisUniversal::Transcoder::Transcode(array<uint8_t>^ data, String^ name)
{	
	auto nameC = msclr::interop::marshal_as < std::string>(name);

	try
	{
		pin_ptr<uint8_t> pData = &data[0];

		basisu::vector<uint8_t> file;
		file.append(pData, data->Length);
		auto output = transcoder->Transcode(file, nameC);
		
		return CreateManagedBuffer(output);
	}
	catch (std::exception& exception)
	{
		auto message = gcnew String(exception.what());
		throw gcnew Exception(message);
	}
}

inline array<Byte>^ SuperCompressed::BasisUniversal::Transcoder::CreateManagedBuffer(basisu::uint8_vec output)
{
	auto buffer = gcnew array<Byte>((int)output.size());
	pin_ptr<Byte> bufferStart = &buffer[0];
	memcpy_s(bufferStart, buffer->Length, &output[0], output.size());

	return buffer;
}
