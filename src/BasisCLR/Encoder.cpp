#include "Encoder.h"
#include "NativeEncoder.h"

#include <string>
#include <assert.h>
#include <msclr\marshal_cppstd.h>

using namespace System;

SuperCompressed::BasisUniversal::Encoder::Encoder()
{
	encoder = new NativeEncoder();
	encoder->Init();	
}

SuperCompressed::BasisUniversal::Encoder::~Encoder()
{
	if (encoder != nullptr)
	{
		encoder->Deinit();
		delete encoder;
		encoder = nullptr;
	}
}

array<System::Byte>^ SuperCompressed::BasisUniversal::Encoder::EncodeEtc1s(System::String^ filename, System::Nullable<int> quality, System::Nullable<bool> perceptual, System::Nullable<bool> generateMipmaps, System::Nullable<bool> renormalize)
{
	assert(encoder != nullptr);
	
	if (!quality.HasValue) { quality = 128; }
	if (!perceptual.HasValue) { perceptual = true; }
	if (!generateMipmaps.HasValue) { generateMipmaps= false; }
	if (!renormalize.HasValue) { renormalize = false; }

	if (quality.Value < 0 || quality.Value > 255)
	{
		throw gcnew System::ArgumentOutOfRangeException("quality", quality.Value, "quality should be in [0..255]");
	}
		
	auto filenameC = msclr::interop::marshal_as<std::string>(filename);

	try
	{
		auto output = encoder->Encode(filenameC, false, quality.Value, perceptual.Value, generateMipmaps.Value, renormalize.Value);
		return CreateManagedBuffer(output);
	}
	catch (std::exception& exception)
	{
		auto message = gcnew String(exception.what());
		throw gcnew Exception(message);
	}
}

array<System::Byte>^ SuperCompressed::BasisUniversal::Encoder::EncodeUastc(System::String^ filename, System::Nullable<int> level, System::Nullable<bool> perceptual, System::Nullable<bool> generateMipmaps, System::Nullable<bool> renormalize)
{
	assert(encoder != nullptr);

	if (!level.HasValue) { level = 3; }
	if (!perceptual.HasValue) { perceptual = true; }
	if (!generateMipmaps.HasValue) { generateMipmaps = false; }
	if (!renormalize.HasValue) { renormalize = false; }

	if (level.Value < 0 || level.Value > 4)
	{
		throw gcnew System::ArgumentOutOfRangeException("level", level.Value, "level should be in [0..4]");
	}

	auto filenameC = msclr::interop::marshal_as<std::string>(filename);

	try
	{
		auto output = encoder->Encode(filenameC, true, level.Value, perceptual.Value, generateMipmaps.Value, renormalize.Value);
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
