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

			/// <summary>
			/// Foooreare
			/// </summary>
			/// <param name="data">Intput foo</param>
			/// <param name="width"></param>
			/// <param name="height"></param>
			/// <param name="quality"></param>
			/// <param name="perceptual"></param>
			/// <param name="generateMipmaps"></param>
			/// <param name="renormalize"></param>
			/// <returns></returns>
			array<System::Byte>^ EncodeEtc1s(array<uint8_t>^ data, uint32_t width, uint32_t height, 
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<int> quality,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> perceptual,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> generateMipmaps,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> renormalize);

			array<System::Byte>^ EncodeUastc(array<uint8_t>^ data, uint32_t width, uint32_t height,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<int> level,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> perceptual,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> generateMipmaps,
				[System::Runtime::InteropServices::OptionalAttribute] System::Nullable<bool> renormalize);

			array<System::Byte>^ Encode(array<uint8_t>^ data, uint32_t width, uint32_t height, System::String^ name);
			array<System::Byte>^ Encode(System::String^ filename);
		private:
			array<System::Byte>^ CreateManagedBuffer(basisu::uint8_vec output);
		};		
	}
}
