#include "EncoderSettings.h"
#include "Settings.h"

SuperCompressed::BasisUniversal::EncoderSettings::EncoderSettings()
{	
	settings = gcnew array<float>(encoder_settings::max_encoder_settings);
}

void SuperCompressed::BasisUniversal::EncoderSettings::CopyTo(std::vector<float> &target)
{	
	target.resize(settings->Length);
	for (int i = 0; i < settings->Length; i++)
	{
		target[i] = settings[i];
	}
}
