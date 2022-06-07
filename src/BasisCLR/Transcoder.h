#pragma once
#include <cstdint>
#include <basisu.h>

class NativeTranscoder;

namespace SuperCompressed
{
	namespace BasisUniversal
	{		
		public ref class Transcoder : System::IDisposable
		{
		private:
			NativeTranscoder* transcoder;

		public:
			Transcoder();
			~Transcoder();

			int32_t GetImageCount(array<uint8_t>^ data);
			int32_t GetMipMapCount(array<uint8_t>^ data, int32_t image);

			array<System::Byte>^ Transcode(array<uint8_t>^ data, int32_t image, int32_t mipmap,
				[System::Runtime::InteropServices::OutAttribute] int32_t% width,
				[System::Runtime::InteropServices::OutAttribute] int32_t% height,
				[System::Runtime::InteropServices::OutAttribute] int32_t% pitch);
		private:
			array<System::Byte>^ ConvertToManagedBuffer(basisu::uint8_vec output);
		};
	}
}
