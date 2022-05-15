#include "Encoder.h"
#include <basisu.h>
////#include <basisu_transcoder_internal.h>
#include <basisu_enc.h>

#pragma managed(push, off)

void Encoder::Init()
{
	basisu::basisu_encoder_init();
}

#pragma managed(pop)