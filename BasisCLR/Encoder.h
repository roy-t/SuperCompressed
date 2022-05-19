#pragma once

using namespace System;

class NativeEncoder;

namespace SuperCompressed 
{
	namespace BasisUniversal
	{		
		ref class EncoderSettings;

		public ref class Encoder : IDisposable
		{
		private:
			NativeEncoder* encoder;

		public:
			Encoder();
			~Encoder();

			array<Byte>^ Encode(array<uint8_t>^ data, uint32_t width, uint32_t height, String^ name);
			array<Byte>^ Encode(String^ filename);
		private:
			array<Byte>^ CreateManagedBuffer(basisu::uint8_vec output);
		};		
	}
}
