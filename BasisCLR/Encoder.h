#pragma once
#include <cstdint>
#include <basisu.h>

class NativeEncoder;

namespace SuperCompressed 
{
	namespace BasisUniversal
	{
		public ref class Encoder : System::IDisposable
		{
		private:
			NativeEncoder* encoder;

		public:
			Encoder();
			~Encoder();

			array<System::Byte>^ Encode(array<uint8_t>^ data, uint32_t width, uint32_t height, System::String^ name);
			array<System::Byte>^ Encode(System::String^ filename);
		private:
			array<System::Byte>^ CreateManagedBuffer(basisu::uint8_vec output);
		};		
	}
}
