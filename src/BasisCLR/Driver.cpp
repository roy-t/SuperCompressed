#include "pch.h"
#include "Driver.h"

#include "Encoder.h"

Driver::Driver()
{
	Encoder* enc = new Encoder();
	enc->Init();
}
