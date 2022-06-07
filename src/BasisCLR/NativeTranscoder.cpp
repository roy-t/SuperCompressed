#include "NativeTranscoder.h"

#include <basisu_enc.h>
#include <basisu_transcoder.h>
#include <fmt/format.h>

using namespace basisu;
using namespace basist;

void NativeTranscoder::Init()
{
	basisu_transcoder_init();
}

uint32_t NativeTranscoder::GetImageCount(basisu::vector<uint8_t> file)
{
	const transcoder_texture_format format = transcoder_texture_format::cTFBC7_RGBA;
	const uint32_t flags = 0;

	basisu_transcoder transcoder{};

	if (!transcoder.validate_header(file.data(), file.size()))
	{
		std::string error = fmt::format("Header validation failed");
		throw std::exception(error.c_str());
	}

	basisu_file_info info;
	if (!transcoder.get_file_info(file.data(), file.size(), info))
	{
		std::string error = fmt::format("Loading file info failed");
		throw std::exception(error.c_str());
	}

	return info.m_total_images;
}

uint32_t NativeTranscoder::GetMipMapCount(basisu::vector<uint8_t> file, uint32_t imageIndex)
{
	const transcoder_texture_format format = transcoder_texture_format::cTFBC7_RGBA;
	const uint32_t flags = 0;

	basisu_transcoder transcoder{};

	if (!transcoder.validate_header(file.data(), file.size()))
	{
		std::string error = fmt::format("Header validation failed");
		throw std::exception(error.c_str());
	}

	basisu_file_info info;
	if (!transcoder.get_file_info(file.data(), file.size(), info))
	{
		std::string error = fmt::format("Loading file info failed");
		throw std::exception(error.c_str());
	}

	if (imageIndex >= info.m_total_images)
	{
		std::string error = fmt::format("Image index out of range {}/{}", imageIndex, info.m_total_images);
		throw std::exception(error.c_str());
	}

	basisu_image_info image;
	if (!transcoder.get_image_info(file.data(), file.size(), image, imageIndex))
	{
		std::string error = fmt::format("Loading image info failed for index {}", imageIndex);
		throw std::exception(error.c_str());
	}

	return image.m_total_levels;
}

basisu::vector<uint8_t> NativeTranscoder::Transcode(basisu::vector<uint8_t> file, uint32_t imageIndex, uint32_t levelIndex, int32_t& width, int32_t& height, int32_t& pitch)
{
	const transcoder_texture_format format = transcoder_texture_format::cTFBC7_RGBA;
	const uint32_t flags = 0;

	basisu_transcoder transcoder{};

	if (!transcoder.validate_header(file.data(), file.size()))
	{
		std::string error = fmt::format("Header validation failed");
		throw std::exception(error.c_str());
	}

	basisu_file_info info;
	if (!transcoder.get_file_info(file.data(), file.size(), info))
	{
		std::string error = fmt::format("Loading file info failed");
		throw std::exception(error.c_str());
	}
	

	basisu_image_info image;
	if (!transcoder.get_image_info(file.data(), file.size(), image, imageIndex))
	{
		std::string error = fmt::format("Loading image info failed for index {}", imageIndex);
		throw std::exception(error.c_str());
	}

	uint32_t origWidth, origHeight, totalBlocks;
	if (!transcoder.get_image_level_desc(file.data(), file.size(), imageIndex, levelIndex, origWidth, origHeight, totalBlocks))
	{
		std::string error = fmt::format("Loading image level info failed level {}:{}", imageIndex, levelIndex);
		throw std::exception(error.c_str());
	}
	
	basisu::vector<uint8_t> output;

	transcoder.start_transcoding(file.data(), file.size());
	
	uint32_t status;

	width = origWidth;
	height = origHeight;

	if (basis_transcoder_format_is_uncompressed(format))
	{
		const uint32_t bytesPerPixel = basis_get_uncompressed_bytes_per_pixel(format);
		const uint32_t bytesPerLine = origWidth * bytesPerPixel;
		const uint32_t bytesPerSlice = bytesPerLine * origHeight;

		pitch = bytesPerLine;

		output.resize(bytesPerSlice);

		status = transcoder.transcode_image_level(
			file.data(),
			file.size(),
			imageIndex,
			levelIndex,
			output.data(),
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
		uint32_t requiredSize = totalBlocks * bytesPerBlock;
		
		pitch = bytesPerBlock * blocksPerLine;

		// Add required extra padding for this format
		if (format == transcoder_texture_format::cTFPVRTC1_4_RGB
			|| format == transcoder_texture_format::cTFPVRTC1_4_RGBA)
		{
			const uint32_t width = (origWidth + 3) & ~3;
			const uint32_t height = (origHeight + 3) & ~3;
			requiredSize = (std::max(8U, width) * std::max(8U, height) * 4 + 7) / 8;
			assert(requiredSize >= totalBlocks * bytesPerBlock);
		}

		output.resize(requiredSize);

		status = transcoder.transcode_image_level(
			file.data(),
			file.size(),
			imageIndex,
			levelIndex,
			output.data(),
			output.size() / bytesPerBlock,
			format,
			flags);
	}

	if (!status)
	{
		std::string error = fmt::format("Transcoding failed for {}:{}", imageIndex, levelIndex);
		throw std::exception(error.c_str());
	}
	
	transcoder.stop_transcoding();

	return output;
}