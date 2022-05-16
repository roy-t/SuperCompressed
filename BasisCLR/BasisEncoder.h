#pragma once

using namespace System;

class Encoder;

namespace SuperCompressed {
	namespace BasisUniversal
	{
		public ref class BasisEncoder : IDisposable
		{
		private:
			Encoder* encoder;

		public:
			BasisEncoder();
			~BasisEncoder();
		};
	}
}
