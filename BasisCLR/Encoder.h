#pragma once

using namespace System;

class NativeEncoder;

namespace SuperCompressed {
	namespace BasisUniversal
	{
		public ref class EncoderSettings
		{

		public:
			EncoderSettings::EncoderSettings();

			/// <summary>
			/// Threads is the TOTAL number of job pool threads, including the calling thread! So 2=1 new thread, 3=2 new threads, etc.
			/// </summary>
			uint32_t Threads;

			/// <summary>
			/// Use perceptual sRGB colorspace metrics instead of linear
			/// </summary>
			bool Perceptual;

			/// <summary>
			/// Check to see if any input image has an alpha channel, if so then the output basis file will have alpha channels
			/// </summary>
			bool Alpha;

			/// <summary>
			/// True to generate UASTC .basis file data, otherwise ETC1S.
			/// </summary>
			bool Uastc;

			/// <summary>
			/// Mipmap generation
			/// </summary>
			bool Mipmap;
		};

		public ref class Encoder : IDisposable
		{
		private:
			NativeEncoder* encoder;

		public:
			Encoder();
			~Encoder();

		public:
			array<Byte>^ Encode(String^ filename, EncoderSettings^ settings);
		};		
	}
}
