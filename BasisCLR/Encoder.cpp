#include "Encoder.h"

#include <basisu.h>
#include <basisu_enc.h>
#include <fmt/format.h>

void Encoder::Init()
{
	basisu::basisu_encoder_init();
}

void Encoder::Encode(const std::string &filename)
{
	basisu::image image;
	if (!basisu::load_image(filename, image))
	{
		std::string error = fmt::format("Failed to load image {}.", filename);		
		throw std::exception(error.c_str());
	}
}

void Encoder::Deinit()
{
	basisu::basisu_encoder_deinit();
}
