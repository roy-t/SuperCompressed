#include "Encoder.h"

CompressedTexture Encode(uint8_t* buffer, int32_t width, int32_t heigth, Mode mode, MipMapGeneration mipMapGeneration, Quality quality)
{
	CompressedTexture texture = CompressedTexture();
	texture.ByteLength = 64;
	texture.Buffer = (uint8_t*)malloc(texture.ByteLength);

	return texture;
}

void Free(uint8_t* buffer)
{
	free(buffer);
}
