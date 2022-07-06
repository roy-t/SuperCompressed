#include "pch.h"
#include "Transcoder.h"

using namespace basisu;
using namespace basist;

void InitializeTranscoder()
{
    basisu_transcoder_init();
}

int32_t GetImageCount(uint8_t* file, int32_t length)
{
	const uint32_t ulength = (uint32_t)length;

	basisu_transcoder transcoder{};

	if (!transcoder.validate_header(file, ulength))
	{
		return -TranscodeErrors::InvalidHeader;
	}

	basisu_file_info info;
	if (!transcoder.get_file_info(file, ulength, info))
	{
		return -TranscodeErrors::InvalidFileInfo;
	}

	return (int32_t)info.m_total_images;
}

int32_t GetLevelCount(uint8_t* data, int32_t length, int32_t imageIndex)
{
	const uint32_t ulength = (uint32_t)length;
	const uint32_t uimageIndex = (uint32_t)imageIndex;

	basisu_transcoder transcoder{};

	if (!transcoder.validate_header(data, length))
	{
		return -TranscodeErrors::InvalidHeader;
	}

	basisu_file_info info;
	if (!transcoder.get_file_info(data, ulength, info))
	{
		return -TranscodeErrors::InvalidFileInfo;
	}

	if (uimageIndex >= info.m_total_images)
	{
		return -TranscodeErrors::ImageIndexOutOfRange;
	}

	basisu_image_info image;
	if (!transcoder.get_image_info(data, length, image, uimageIndex))
	{
		return -TranscodeErrors::InvalidImageInfo;
	}

	return image.m_total_levels;
}

TranscodedTexture Transcode(uint8_t* data, int32_t length, int32_t imageIndex, int32_t levelIndex, Format targetFormat)
{
	const uint32_t ulength = (uint32_t)length;
	const uint32_t uimageIndex = (uint32_t)imageIndex;
	const transcoder_texture_format format = (transcoder_texture_format)targetFormat;
	const uint32_t flags = 0;

	basisu_transcoder transcoder{};

	if (!transcoder.validate_header(data, length))
	{
		return { TranscodeErrors::InvalidHeader, nullptr, 0, 0, 0, 0};
	}

	basisu_file_info info;
	if (!transcoder.get_file_info(data, ulength, info))
	{
		return { TranscodeErrors::InvalidFileInfo, nullptr, 0, 0, 0, 0 };		
	}

	if (uimageIndex >= info.m_total_images)
	{
		return { TranscodeErrors::ImageIndexOutOfRange, nullptr, 0, 0, 0, 0 };
	}

	basisu_image_info image;
	if (!transcoder.get_image_info(data, length, image, uimageIndex))
	{
		return { TranscodeErrors::InvalidImageInfo, nullptr, 0, 0, 0, 0 };
	}

	uint32_t origWidth, origHeight, totalBlocks;
	if (!transcoder.get_image_level_desc(data, ulength, uimageIndex, levelIndex, origWidth, origHeight, totalBlocks))
	{
		return { TranscodeErrors::InvalidImageLevelDescription, nullptr, 0, 0, 0, 0 };
	}

	uint8_t* pData = nullptr;
	uint32_t dataLength = 0;

	transcoder.start_transcoding(data, ulength);

	uint32_t status;

	origWidth;
	origHeight;
	uint32_t pitch = 0;

	if (basis_transcoder_format_is_uncompressed(format))
	{
		const uint32_t bytesPerPixel = basis_get_uncompressed_bytes_per_pixel(format);
		const uint32_t bytesPerLine = origWidth * bytesPerPixel;
		dataLength = bytesPerLine * origHeight;

		pitch = bytesPerLine;

		pData = (uint8_t*)malloc(dataLength);
		if (pData == nullptr)
		{
			return { TranscodeErrors::OutOfMemory, nullptr, 0, 0, 0, 0 };
		}

		status = transcoder.transcode_image_level(
			data,
			ulength,
			imageIndex,
			levelIndex,
			pData,
			origWidth * origHeight,
			format,
			flags,
			origWidth,
			nullptr,
			origHeight);
	}
	else
	{
		const uint32_t bytesPerBlock = basis_get_bytes_per_block_or_pixel(format);
		const uint32_t blockWidth = basis_get_block_width(format);
		const uint32_t blocksPerLine = origWidth / blockWidth;
		dataLength = totalBlocks * bytesPerBlock;

		pitch = bytesPerBlock * blocksPerLine;

		// Add required extra padding for this format
		if (format == transcoder_texture_format::cTFPVRTC1_4_RGB
			|| format == transcoder_texture_format::cTFPVRTC1_4_RGBA)
		{
			const uint32_t width = (origWidth + 3) & ~3;
			const uint32_t height = (origHeight + 3) & ~3;
			dataLength = (std::max(8U, width) * std::max(8U, height) * 4 + 7) / 8;
			assert(dataLength >= totalBlocks * bytesPerBlock);
		}

		pData = (uint8_t*)malloc(dataLength);
		if (pData == nullptr)
		{
			return { TranscodeErrors::OutOfMemory, nullptr, 0, 0, 0, 0 };
		}

		status = transcoder.transcode_image_level(
			data,
			ulength,
			imageIndex,
			levelIndex,
			pData,
			dataLength / bytesPerBlock,
			format,
			flags);
	}

	if (!status)
	{
		return { TranscodeErrors::Failed, nullptr, 0, 0, 0, 0 };		
	}	
	
	transcoder.stop_transcoding();

	return { TranscodeErrors::None, pData, (int32_t)dataLength, (int32_t)origWidth, (int32_t)origHeight, (int32_t)pitch };
}

void FreeTranscodedTexture(TranscodedTexture texture)
{
	free((void*)texture.Buffer);
}
