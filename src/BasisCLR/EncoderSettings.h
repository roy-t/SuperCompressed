#pragma once
#include <cstdint>
#include <vector>
#include "Settings.h"

namespace SuperCompressed
{
	namespace BasisUniversal
	{	
        public enum class Ktx2Supercompression : uint32_t
        {
            None = 0,
            BasisLz = 1,
            Standard = 2
        };

        public enum class PackUastcLevel : uint32_t
        {
            // Fastest is the lowest quality, although it's stil substantially higher quality vs. BC1/ETC1. It supports 5 modes.
            // The output may be somewhat blocky because this setting doesn't support 2/3-subset UASTC modes, but it should be less blocky vs. BC1/ETC1.
            // This setting doesn't write BC1 hints, so BC1 transcoding will be slower. 
            // Transcoded ETC1 quality will be lower because it only considers 2 hints out of 32.
            // Avg. 43.45 dB
            Fastest = 0,

            // Faster is ~3x slower than fastest. It supports 9 modes.
            // Avg. 46.49 dB
            Faster = 1,

            // Default is ~5.5x slower than fastest. It supports 14 modes.
            // Avg. 47.47 dB
            Default = 2,

            // Slower is ~14.5x slower than fastest. It supports all 18 modes.
            // Avg. 48.01 dB
            Slower = 3,

            // VerySlow is ~200x slower than fastest. 
            // The best quality the codec is capable of, but you'll need to be patient or have a lot of cores.
            // Avg. 48.24 dB
            VerySlow = 4,

            Mask = 0xF,

            // By default the encoder tries to strike a balance between UASTC and transcoded BC7 quality.
            // These flags allow you to favor only optimizing for lowest UASTC error, or lowest BC7 error.
            FavorUASTCError = 8,
            FavorBC7Error = 16,

            ETC1FasterHints = 64,
            ETC1FastestHints = 128,
            ETC1DisableFlipAndIndividual = 256,

            // Favor UASTC modes 0 and 10 more than the others (this is experimental, it's useful for RDO compression)
            FavorSimplerModes = 512,
        };


		public ref class EncoderSettings
		{
			private:
				array<float>^ settings;

			public:
				EncoderSettings();
				
                property uint32_t compression_level
                {
                    uint32_t get() { return reinterpret_as_uint(settings[encoder_settings::compression_level]); }
                    void set(uint32_t value) { settings[encoder_settings::compression_level] = reinterpret_as_float(value); }
                }
                property float selector_rdo_thresh
                {
                    float get() { return settings[encoder_settings::selector_rdo_thresh]; }
                    void set(float value) { settings[encoder_settings::selector_rdo_thresh] = value; }
                }
                property float endpoint_rdo_thresh
                {
                    float get() { return settings[encoder_settings::endpoint_rdo_thresh]; }
                    void set(float value) { settings[encoder_settings::endpoint_rdo_thresh] = value; }
                }
                property float mip_scale
                {
                    float get() { return settings[encoder_settings::mip_scale]; }
                    void set(float value) { settings[encoder_settings::mip_scale] = value; }
                }
                property uint32_t mip_smallest_dimension
                {
                    uint32_t get() { return reinterpret_as_uint(settings[encoder_settings::mip_smallest_dimension]); }
                    void set(uint32_t value) { settings[encoder_settings::mip_smallest_dimension] = reinterpret_as_float(value); }
                }
                property uint32_t max_endpoint_clusters
                {
                    uint32_t get() { return reinterpret_as_uint(settings[encoder_settings::max_endpoint_clusters]); }
                    void set(uint32_t value) { settings[encoder_settings::max_endpoint_clusters] = reinterpret_as_float(value); }
                }
                property uint32_t max_selector_clusters
                {
                    uint32_t get() { return reinterpret_as_uint(settings[encoder_settings::max_selector_clusters]); }
                    void set(uint32_t value) { settings[encoder_settings::max_selector_clusters] = reinterpret_as_float(value); }
                }
                property int32_t quality_level
                {
                    int32_t get() { return reinterpret_as_int(settings[encoder_settings::quality_level]); }
                    void set(int32_t value) { settings[encoder_settings::quality_level] = reinterpret_as_float(value); }
                }

                property PackUastcLevel pack_uastc_flags
                {
                    PackUastcLevel get() { return (PackUastcLevel)reinterpret_as_uint(settings[encoder_settings::pack_uastc_flags]); }
                    void set(PackUastcLevel value) { settings[encoder_settings::pack_uastc_flags] = reinterpret_as_float((uint32_t)value); }
                }
                property float rdo_uastc_quality_scalar
                {
                    float get() { return settings[encoder_settings::rdo_uastc_quality_scalar]; }
                    void set(float value) { settings[encoder_settings::rdo_uastc_quality_scalar] = value; }
                }
                property uint32_t rdo_uastc_dict_size
                {
                    uint32_t get() { return reinterpret_as_uint(settings[encoder_settings::rdo_uastc_dict_size]); }
                    void set(uint32_t value) { settings[encoder_settings::rdo_uastc_dict_size] = reinterpret_as_float(value); }
                }
                property float rdo_uastc_max_smooth_block_error_scale
                {
                    float get() { return settings[encoder_settings::rdo_uastc_max_smooth_block_error_scale]; }
                    void set(float value) { settings[encoder_settings::rdo_uastc_max_smooth_block_error_scale] = value; }
                }
                property float rdo_uastc_smooth_block_max_std_dev
                {
                    float get() { return settings[encoder_settings::rdo_uastc_smooth_block_max_std_dev]; }
                    void set(float value) { settings[encoder_settings::rdo_uastc_smooth_block_max_std_dev] = value; }
                }
                property float rdo_uastc_max_allowed_rms_increase_ratio
                {
                    float get() { return settings[encoder_settings::rdo_uastc_max_allowed_rms_increase_ratio]; }
                    void set(float value) { settings[encoder_settings::rdo_uastc_max_allowed_rms_increase_ratio] = value; }
                }
                property float rdo_uastc_skip_block_rms_thresh
                {
                    float get() { return settings[encoder_settings::rdo_uastc_skip_block_rms_thresh]; }
                    void set(float value) { settings[encoder_settings::rdo_uastc_skip_block_rms_thresh] = value; }
                }
                property uint32_t resample_width
                {
                    uint32_t get() { return reinterpret_as_uint(settings[encoder_settings::resample_width]); }
                    void set(uint32_t value) { settings[encoder_settings::resample_width] = reinterpret_as_float(value); }
                }
                property uint32_t resample_height
                {
                    uint32_t get() { return reinterpret_as_uint(settings[encoder_settings::resample_height]); }
                    void set(uint32_t value) { settings[encoder_settings::resample_height] = reinterpret_as_float(value); }
                }
                property float resample_factor
                {
                    float get() { return settings[encoder_settings::resample_factor]; }
                    void set(float value) { settings[encoder_settings::resample_factor] = value; }
                }

                property Ktx2Supercompression ktx2_uastc_supercompression
                {
                    Ktx2Supercompression get() { return (Ktx2Supercompression)reinterpret_as_uint(settings[encoder_settings::ktx2_uastc_supercompression]); }
                    void set(Ktx2Supercompression value) { settings[encoder_settings::ktx2_uastc_supercompression] = reinterpret_as_float((uint32_t)value); }
                }
                property uint32_t ktx2_zstd_supercompression_level
                {
                    uint32_t get() { return reinterpret_as_uint(settings[encoder_settings::ktx2_zstd_supercompression_level]); }
                    void set(uint32_t value) { settings[encoder_settings::ktx2_zstd_supercompression_level] = reinterpret_as_float(value); }
                }                

			internal:
				void CopyTo(std::vector<float> &target);
		};
	}
}



