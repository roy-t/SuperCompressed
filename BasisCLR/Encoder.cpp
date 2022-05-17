#include "NativeEncoder.h"

#include <assert.h>
#include <msclr\marshal_cppstd.h>

#include "Encoder.h"
#include <basisu.h>

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
		this->encoder = nullptr;
	}
}

array<Byte>^ SuperCompressed::BasisUniversal::Encoder::Encode(String^ filename)
{
	assert(this->encoder != nullptr);

	auto filenameC = msclr::interop::marshal_as<std::string>(filename);

	try
	{
		auto output = this->encoder->Encode(filenameC);
		
		// TODO: that's 2 memcopies, on here and one inside encoder?
		auto buffer = gcnew array<Byte>((int)output.size());
		pin_ptr<Byte> bufferStart = &buffer[0];		
		memcpy_s(bufferStart, buffer->Length, &output[0], output.size());


		return buffer;
	}
	catch (std::exception& exception)
	{
		auto message = gcnew String(exception.what());
		throw gcnew Exception(message);
	}	
}
