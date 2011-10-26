#include "ohiio.h"
using namespace OpenImageIO;

//extern "C" {



/****************************
 *
 *  class QuantizationSpec
 *
 ****************************/


int QSpecCreate_0 (QuantizationSpec **qsptr,
                   int _black, 
                   int _white, 
                   int _min, 
                   int _max) {
    *qsptr = new QuantizationSpec(_black, _white, _min, _max);
    return 0;
}

int QSpecCreate_1 (QuantizationSpec **qsptr,
                   TypeDesc _type) {
    
    *qsptr = new QuantizationSpec(_type);
    return 0;
}



/****************************
 *
 *  class ImageSpec
 *
 ****************************/

/// Constructor: given just the data format, set the default quantize
/// and set all other channels to something reasonable.
int ImageSpecCreate_0 (ImageSpec **isptr,
                       TypeDesc format) {
    
    *isptr = new ImageSpec(format);
    return 0;
}

/// Constructor for simple 2D scanline image with nothing special.
/// If fmt is not supplied, default to unsigned 8-bit data.
int ImageSpecCreate_1 (ImageSpec **isptr,
                       int xres, int yres, 
                       int nchans, 
                       TypeDesc fmt) {
    
    *isptr = new ImageSpec(xres, yres, nchans, fmt);
    return 0;
}

/// Set the data format, and as a side effect set quantize
/// to good defaults for that format
void ImageSpec_set_format (ImageSpec *imageSpec,
                           TypeDesc fmt) {
    imageSpec->set_format(fmt);

}

/// Set the channelnames to reasonable defaults ("R", "G", "B", "A"),
/// and alpha_channel, based on the number of channels.
void ImageSpec_default_channel_names (ImageSpec *imageSpec) {
    imageSpec->default_channel_names();
}

/// Given quantization parameters, deduce a TypeDesc that can
/// be used without unacceptable loss of significant bits.
TypeDesc format_from_quantize (ImageSpec *imageSpec,
                                            int quant_black, int quant_white,
                                            int quant_min, int quant_max) {
    return imageSpec->format_from_quantize(quant_black, quant_white, quant_min, quant_max);
}

size_t ImageSpec_channel_bytes_0 (const ImageSpec *imageSpec) {
    return imageSpec->channel_bytes();
}


size_t ImageSpec_channel_bytes_1 (ImageSpec *imageSpec,
                                  int chan, bool native) {
    return imageSpec->channel_bytes(chan, native);
}

size_t ImageSpec_pixel_bytes_0 (ImageSpec *imageSpec,
                                bool native) {
    return imageSpec->pixel_bytes(native);
}

size_t ImageSpec_pixel_bytes_1 (ImageSpec *imageSpec,
                                int firstchan, int nchans, bool native) {
    return imageSpec->pixel_bytes(firstchan, nchans, native);
}

OpenImageIO::imagesize_t ImageSpec_scanline_bytes (ImageSpec *imageSpec,
                                                   bool native) {
    return imageSpec->scanline_bytes(native);
}

OpenImageIO::imagesize_t ImageSpec_tile_pixels (ImageSpec *imageSpec) {
    return imageSpec->tile_pixels();
}

OpenImageIO::imagesize_t ImageSpec_tile_bytes (ImageSpec *imageSpec,
                                               bool native) {
    return imageSpec->tile_bytes(native);
}

OpenImageIO::imagesize_t ImageSpec_image_pixels (ImageSpec *imageSpec) {
    return imageSpec->image_pixels();
}

OpenImageIO::imagesize_t ImageSpec_image_bytes (ImageSpec *imageSpec,
                                                bool native) {
    return imageSpec->image_bytes(native);
}

bool ImageSpec_size_t_safe(OpenImageIO::ImageSpec *imageSpec) {
    return imageSpec->size_t_safe();
}




/****************************
 *
 *  class ImageInput
 *
 ****************************/


int ImageInputCreate (ImageInput **iiptr,
                      char *filename,
                      char *plugin_searchpath) {
    *iiptr = ImageInput::create(filename, plugin_searchpath);
    return 0;
}


/// Simple read_scanline reads to contiguous float pixels.
bool ImageInput_read_scanline (ImageInput *imageInput,
                               int y, 
                               int z, 
                               float *data) {
    
    return imageInput->read_scanline (y, z, TypeDesc::FLOAT, data);

}

///
/// Simple read_image reads to contiguous float pixels.
bool ImageInput_read_image (ImageInput *imageInput, 
                            float *data) {
    return imageInput->read_image (TypeDesc::FLOAT, data);
}


//}

