using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LibKtxDotNet
{
    public enum ktx_error_code_e
    {
        KTX_SUCCESS = 0,         /*!< Operation was successful. */
        KTX_FILE_DATA_ERROR,     /*!< The data in the file is inconsistent with the spec. */
        KTX_FILE_ISPIPE,         /*!< The file is a pipe or named pipe. */
        KTX_FILE_OPEN_FAILED,    /*!< The target file could not be opened. */
        KTX_FILE_OVERFLOW,       /*!< The operation would exceed the max file size. */
        KTX_FILE_READ_ERROR,     /*!< An error occurred while reading from the file. */
        KTX_FILE_SEEK_ERROR,     /*!< An error occurred while seeking in the file. */
        KTX_FILE_UNEXPECTED_EOF, /*!< File does not have enough data to satisfy request. */
        KTX_FILE_WRITE_ERROR,    /*!< An error occurred while writing to the file. */
        KTX_GL_ERROR,            /*!< GL operations resulted in an error. */
        KTX_INVALID_OPERATION,   /*!< The operation is not allowed in the current state. */
        KTX_INVALID_VALUE,       /*!< A parameter value was not valid */
        KTX_NOT_FOUND,           /*!< Requested key was not found */
        KTX_OUT_OF_MEMORY,       /*!< Not enough memory to complete the operation. */
        KTX_TRANSCODE_FAILED,    /*!< Transcoding of block compressed texture failed. */
        KTX_UNKNOWN_FILE_FORMAT, /*!< The file not a KTX file */
        KTX_UNSUPPORTED_TEXTURE_TYPE, /*!< The KTX file specifies an unsupported texture type. */
        KTX_UNSUPPORTED_FEATURE,  /*!< Feature not included in in-use library or not yet implemented. */
        KTX_LIBRARY_NOT_LINKED,  /*!< Library dependency (OpenGL or Vulkan) not linked into application. */
        KTX_ERROR_MAX_ENUM = KTX_LIBRARY_NOT_LINKED /*!< For safety checks. */
    }

    [Flags]
    public enum ktxTextureCreateFlagBits
    {
        KTX_TEXTURE_CREATE_NO_FLAGS = 0x00,
        KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT = 0x01,
        /*!< Load the images from the KTX source. */
        KTX_TEXTURE_CREATE_RAW_KVDATA_BIT = 0x02,
        /*!< Load the raw key-value data instead of
             creating a @c ktxHashList from it. */
        KTX_TEXTURE_CREATE_SKIP_KVDATA_BIT = 0x04
        /*!< Skip any key-value data. This overrides
             the RAW_KVDATA_BIT. */
    }

    public static class NativeMethods
    {
        /// <summary>
        /// Create a ktxTexture1 or ktxTexture2 from a named KTX file according to the file contents.
        /// </summary>
        [DllImport("ktx", CharSet = CharSet.Ansi)]
        public static extern ktx_error_code_e ktxTexture_CreateFromNamedFile(string filename, ktxTextureCreateFlagBits createFlags, out IntPtr texture);
    }
}
