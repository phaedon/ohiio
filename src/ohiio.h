/**
 * ohiio -- C-compatible wrappers for the C++ classes in OIIO
 * ================
 * Phaedon Sinis
 * October 2011
 */



#ifndef __OHIIO_H__
#define __OHIIO_H__

#include "imageio.h"
using namespace OpenImageIO;

extern "C" {

    /****************************
     *
     *  class QuantizationSpec
     *
     ****************************/
    
    int QSpecCreate_0 (QuantizationSpec **qsptr,
                                   int _black, 
                                   int _white, 
                                   int _min, 
                                   int _max);
    
    int QSpecCreate_1 (QuantizationSpec **qsptr, TypeDesc _type);
    
    
    /****************************
     *
     *  class ImageSpec
     *
     ****************************/
    
    /// Constructor: given just the data format, set the default quantize
    /// and set all other channels to something reasonable.
    int ImageSpecCreate_0 (ImageSpec **isptr,
                           TypeDesc format = TypeDesc::UNKNOWN);

    /// Constructor for simple 2D scanline image with nothing special.
    /// If fmt is not supplied, default to unsigned 8-bit data.
    int ImageSpecCreate_1 (ImageSpec **isptr,
                           int xres, int yres, 
                           int nchans, 
                           TypeDesc fmt = TypeDesc::UINT8);
    
    /// Set the data format, and as a side effect set quantize
    /// to good defaults for that format
    void ImageSpec_set_format (ImageSpec *imageSpec, TypeDesc fmt);
    
    /// Set the channelnames to reasonable defaults ("R", "G", "B", "A"),
    /// and alpha_channel, based on the number of channels.
    void ImageSpec_default_channel_names (ImageSpec *imageSpec);
    
    /// Given quantization parameters, deduce a TypeDesc that can
    /// be used without unacceptable loss of significant bits.
    TypeDesc format_from_quantize (ImageSpec *imageSpec,
                                   int quant_black, int quant_white,
                                   int quant_min, int quant_max);
    
    size_t ImageSpec_channel_bytes_0 (const ImageSpec *imageSpec);
    
    size_t ImageSpec_channel_bytes_1 (const ImageSpec *imageSpec,
                                      int chan, bool native=false);
    
    size_t ImageSpec_pixel_bytes_0 (const ImageSpec *imageSpec, bool native=false);
    
    size_t ImageSpec_pixel_bytes_1 (const ImageSpec *imageSpec,
                                    int firstchan, int nchans, bool native=false);
    
    imagesize_t ImageSpec_scanline_bytes (const ImageSpec *imageSpec, bool native=false);
    
    imagesize_t ImageSpec_tile_pixels (const ImageSpec *imageSpec);
    
    imagesize_t ImageSpec_tile_bytes (const ImageSpec *imageSpec, bool native=false);
    
    imagesize_t ImageSpec_image_pixels (const ImageSpec *imageSpec);
    
    imagesize_t ImageSpec_image_bytes (const ImageSpec *imageSpec, bool native=false);
    
    bool ImageSpec_size_t_safe(const ImageSpec *imageSpec);

    void ImageSpec_auto_stride_0 (ImageSpec *imageSpec,
                                  stride_t &xstride, stride_t &ystride,
                             stride_t &zstride, stride_t channelsize,
                             int nchannels, int width, int height);
    
    void ImageSpec_auto_stride_1 (ImageSpec *imageSpec,
                                  stride_t &xstride, stride_t &ystride,
                             stride_t &zstride, TypeDesc format,
                      int nchannels, int width, int height);
    
    void ImageSpec_auto_stride_2 (ImageSpec *imageSpec,
                                  stride_t &xstride, TypeDesc format, int nchannels);
    
    void ImageSpec_attribute_0 (ImageSpec *imageSpec,
                                const std::string &name, TypeDesc type, const void *value);
    
    void ImageSpec_attribute_1 (ImageSpec *imageSpec,
                                const std::string &name, TypeDesc type, const std::string &value);
    
    void ImageSpec_attribute_2 (ImageSpec *imageSpec,
                                const std::string &name, unsigned int value);
    
    void ImageSpec_attribute_3 (ImageSpec *imageSpec,
                                const std::string &name, int value);
    
    void ImageSpec_attribute_4 (ImageSpec *imageSpec,
                                const std::string &name, float value);
    
    void ImageSpec_attribute_5 (ImageSpec *imageSpec,
                                const std::string &name, const char *value);
    
    void ImageSpec_attribute_6 (ImageSpec *imageSpec,
                                const std::string &name, const std::string &value);
    
    void ImageSpec_erase_attribute (ImageSpec *imageSpec,
                                    const std::string &name,
                          TypeDesc searchtype=TypeDesc::UNKNOWN,
                          bool casesensitive=false);

    ImageIOParameter * find_attribute (ImageSpec *imageSpec,
                                       const std::string &name,
                                       TypeDesc searchtype=TypeDesc::UNKNOWN,
                                       bool casesensitive=false);
    
    const ImageIOParameter *ImageSpec_find_attribute (const ImageSpec *imageSpec,
                                                      const std::string &name,
                                            TypeDesc searchtype=TypeDesc::UNKNOWN,
                                            bool casesensitive=false);
    
    int ImageSpec_get_int_attribute (const ImageSpec *imageSpec,
                                     const std::string &name, int defaultval=0);
    
    float ImageSpec_get_float_attribute (const ImageSpec *imageSpec,
                                         const std::string &name,
                               float defaultval=0);
    
    const char * ImageSpec_get_string_attribute (const ImageSpec *imageSpec,
                                                const std::string &name,
                                      const std::string &defaultval = std::string());
    
    const char * ImageSpec_metadata_val (const ImageSpec *imageSpec,
                                        const ImageIOParameter &p,
                              bool human=false);
    
    const char * ImageSpec_to_xml (const ImageSpec *imageSpec);

    void ImageSpec_from_xml (ImageSpec *imageSpec,
                             const char *xml);
    
    bool ImageSpec_valid_tile_range (ImageSpec *imageSpec,
                                     int xbegin, int xend, int ybegin, int yend,
                                     int zbegin, int zend);
    
    
    
    /****************************
     *
     *  class ImageInput
     *
     ****************************/
    
    int ImageInputCreate (ImageInput **iiptr,
		       char *filename,
		       char *plugin_searchpath);

    
    /// Simple read_scanline reads to contiguous float pixels.
    bool ImageInput_read_scanline (ImageInput *imageInput,
                                   int y, 
                                   int z, 
                                   float *data);
    
    ///
    /// Simple read_image reads to contiguous float pixels.
    bool ImageInput_read_image (ImageInput *imageInput, 
                                float *data);
    
    
    /****************************
     *
     *  class ImageOutput
     *
     ****************************/
    
}



#endif
