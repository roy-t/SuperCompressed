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

		public:
			array<Byte>^ Encode(String^ filename);
		};		
	}
}
