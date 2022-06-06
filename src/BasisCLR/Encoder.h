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

			array<System::Byte>^ EncodeEtc1s(System::String^ filename,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<int> quality,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> perceptual,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> generateMipmaps,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> renormalize);

			array<System::Byte>^ EncodeUastc(System::String^ filename,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<int> level,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> perceptual,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> generateMipmaps,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> renormalize);

		private:
			array<System::Byte>^ CreateManagedBuffer(basisu::uint8_vec output);
		};		
	}
}
