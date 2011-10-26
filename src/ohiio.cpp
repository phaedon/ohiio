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


size_t ImageSpec_channel_bytes_1 (const ImageSpec *imageSpec,
                                  int chan, bool native) {
    return imageSpec->channel_bytes(chan, native);
}

size_t ImageSpec_pixel_bytes_0 (const ImageSpec *imageSpec,
                                bool native) {
    return imageSpec->pixel_bytes(native);
}

size_t ImageSpec_pixel_bytes_1 (const ImageSpec *imageSpec,
                                int firstchan, int nchans, bool native) {
    return imageSpec->pixel_bytes(firstchan, nchans, native);
}

imagesize_t ImageSpec_scanline_bytes (const ImageSpec *imageSpec,
                                                   bool native) {
    return imageSpec->scanline_bytes(native);
}

imagesize_t ImageSpec_tile_pixels (const ImageSpec *imageSpec) {
    return imageSpec->tile_pixels();
}

imagesize_t ImageSpec_tile_bytes (const ImageSpec *imageSpec,
                                               bool native) {
    return imageSpec->tile_bytes(native);
}

imagesize_t ImageSpec_image_pixels (const ImageSpec *imageSpec) {
    return imageSpec->image_pixels();
}

imagesize_t ImageSpec_image_bytes (const ImageSpec *imageSpec,
                                                bool native) {
    return imageSpec->image_bytes(native);
}

bool ImageSpec_size_t_safe(const ImageSpec *imageSpec) {
    return imageSpec->size_t_safe();
}


void ImageSpec_auto_stride_0 (ImageSpec *imageSpec,
                              stride_t &xstride, stride_t &ystride,
                              stride_t &zstride, stride_t channelsize,
                              int nchannels, int width, int height) {
    imageSpec->auto_stride(xstride, ystride, zstride, channelsize, nchannels, width, height);
}

void ImageSpec_auto_stride_1 (ImageSpec *imageSpec,
                              stride_t &xstride, stride_t &ystride,
                              stride_t &zstride, TypeDesc format,
                              int nchannels, int width, int height) {
    imageSpec->auto_stride(xstride, ystride, zstride, format, nchannels, width, height);
}

void ImageSpec_auto_stride_2 (ImageSpec *imageSpec,
                              stride_t &xstride, TypeDesc format, int nchannels) {
    imageSpec->auto_stride(xstride, format, nchannels);
}

void ImageSpec_attribute_0 (ImageSpec *imageSpec,
                            const std::string &name, TypeDesc type, const void *value) {
    imageSpec->attribute(name, type, value);
}

void ImageSpec_attribute_1 (ImageSpec *imageSpec,
                            const std::string &name, TypeDesc type, const std::string &value) {
    imageSpec->attribute(name, type, value);
}

void ImageSpec_attribute_2 (ImageSpec *imageSpec,
                            const std::string &name, unsigned int value) {
    imageSpec->attribute(name, value);
}

void ImageSpec_attribute_3 (ImageSpec *imageSpec,
                            const std::string &name, int value) {
    imageSpec->attribute(name, value);
}

void ImageSpec_attribute_4 (ImageSpec *imageSpec,
                            const std::string &name, float value) {
    imageSpec->attribute(name, value);
}

void ImageSpec_attribute_5 (ImageSpec *imageSpec,
                            const std::string &name, const char *value) {
    imageSpec->attribute(name, value);
}

void ImageSpec_attribute_6 (ImageSpec *imageSpec,
                            const std::string &name, const std::string &value) {
    imageSpec->attribute(name, value);
}

void ImageSpec_erase_attribute (ImageSpec *imageSpec,
                                const std::string &name,
                                TypeDesc searchtype,
                                bool casesensitive) {
    imageSpec->erase_attribute(name, searchtype, casesensitive);
}

ImageIOParameter * find_attribute (ImageSpec *imageSpec,
                                   const std::string &name,
                                   TypeDesc searchtype,
                                   bool casesensitive) {
    return imageSpec->find_attribute(name, searchtype, casesensitive);
}

const ImageIOParameter *ImageSpec_find_attribute (const ImageSpec *imageSpec,
                                                  const std::string &name,
                                                  TypeDesc searchtype,
                                                  bool casesensitive) {
    return imageSpec->find_attribute(name, searchtype, casesensitive);
}

int ImageSpec_get_int_attribute (const ImageSpec *imageSpec,
                                 const std::string &name, int defaultval) {
    return imageSpec->get_int_attribute(name, defaultval);
}

float ImageSpec_get_float_attribute (const ImageSpec *imageSpec,
                                     const std::string &name,
                                     float defaultval) {
    return imageSpec->get_float_attribute(name, defaultval);
}

const char * ImageSpec_get_string_attribute (const ImageSpec *imageSpec,
                                            const std::string &name,
                                            const std::string &defaultval) {
    return imageSpec->get_string_attribute(name, defaultval).c_str();
}

const char * ImageSpec_metadata_val (const ImageSpec *imageSpec,
                                    const ImageIOParameter &p,
                                    bool human) {
    return imageSpec->metadata_val(p, human).c_str();
}

const char * ImageSpec_to_xml (const ImageSpec *imageSpec) {
    return imageSpec->to_xml().c_str();
}

void ImageSpec_from_xml (ImageSpec *imageSpec,
                         const char *xml) {
    imageSpec->from_xml(xml);
}

bool ImageSpec_valid_tile_range (ImageSpec *imageSpec,
                                 int xbegin, int xend, int ybegin, int yend,
                                 int zbegin, int zend) {
    return imageSpec->valid_tile_range(xbegin, xend, ybegin, yend, zbegin, zend);
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

