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
    
    size_t ImageSpec_channel_bytes_1 (ImageSpec *imageSpec,
                                      int chan, bool native=false);
    
    size_t ImageSpec_pixel_bytes_0 (ImageSpec *imageSpec, bool native=false);
    
    size_t ImageSpec_pixel_bytes_1 (ImageSpec *imageSpec,
                                    int firstchan, int nchans, bool native=false);
    
    imagesize_t ImageSpec_scanline_bytes (ImageSpec *imageSpec, bool native=false);
    
    imagesize_t ImageSpec_tile_pixels (ImageSpec *imageSpec);
    
    imagesize_t ImageSpec_tile_bytes (ImageSpec *imageSpec, bool native=false);
    
    imagesize_t ImageSpec_image_pixels (ImageSpec *imageSpec);
    
    imagesize_t ImageSpec_image_bytes (ImageSpec *imageSpec, bool native=false);
    
    bool ImageSpec_size_t_safe(ImageSpec *imageSpec);


    
    
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
