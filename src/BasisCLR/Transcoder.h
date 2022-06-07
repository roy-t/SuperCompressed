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

			array<System::Byte>^ Transcode(array<uint8_t>^ data,
				[System::Runtime::InteropServices::OutAttribute] int32_t% width,
				[System::Runtime::InteropServices::OutAttribute] int32_t% height,
				[System::Runtime::InteropServices::OutAttribute] int32_t% pitch);
		private:
			array<System::Byte>^ CreateManagedBuffer(basisu::uint8_vec output);
		};
	}
}
