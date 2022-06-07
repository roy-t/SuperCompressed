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

			array<System::Byte>^ Transcode(array<uint8_t>^ data, System::String^ name);
		private:
			array<System::Byte>^ ConvertToManagedBuffer(basisu::uint8_vec output);
		};
	}
}
