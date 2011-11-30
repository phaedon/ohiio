#include "ohiio.h"
#include "imageio.h"




/****************************
 *
 *  class ImageSpec
 *
 ****************************/


/// Constructor: given just the data format, set the default quantize
/// and set all other channels to something reasonable.
ImageSpec *ImageSpecCreate_0 (TypeDesc *format) {
    if (!format) {
        return new ImageSpec();
    } else {
        return new ImageSpec(*format);
    }
}

/// Constructor for simple 2D scanline image with nothing special.
/// If fmt is not supplied, default to unsigned 8-bit data.
ImageSpec *ImageSpecCreate_1 (int xres, int yres, int nchans, 
                              TypeDesc *fmt) {
    
    if (!fmt) {
        return new ImageSpec(xres, yres, nchans);
    } else {
        return new ImageSpec(xres, yres, nchans, *fmt);
    }
}

int ImageSpec_width(ImageSpec *ispec) { return ispec->width; }
int ImageSpec_height(ImageSpec *ispec) {return ispec->height; }
int ImageSpec_nchannels(ImageSpec *ispec) {return ispec->nchannels; }
//TypeDesc *ImageSpec_format(ImageSpec *ispec);


/****************************
 *
 *  class ImageInput
 *
 ****************************/


ImageInput *ImageInputCreate (const char *filename,
                              const char *plugin_searchpath) {
    return ImageInput::create(filename, plugin_searchpath);
}


bool ImageInput_open (ImageInput *imageInput,
                      const char *name, ImageSpec *newspec) {
    return imageInput->open(name, *newspec);
}

bool ImageInput_close (ImageInput *imageInput) {
    return imageInput->close();
}


/// Simple read_image reads to contiguous float pixels.
bool ImageInput_read_image_0 (ImageInput *imageInput, 
                              enum BaseType format,
                              void *data) {
    return imageInput->read_image (TypeDesc( (TypeDesc::BASETYPE) format), data);
}



/// Simple read_image reads to contiguous float pixels.
bool ImageInput_read_image_1 (ImageInput *imageInput, 
                            float *data) {
    return imageInput->read_image (data);
}



/****************************
 *
 *  class ImageOutput
 *
 ****************************/

ImageOutput *ImageOutputCreate (const char *filename,
                                const char *plugin_searchpath) {
    if (plugin_searchpath == NULL) {
        return ImageOutput::create(filename, plugin_searchpath);
    } else {
        return ImageOutput::create(filename, "");
    }
    
}

const char *ImageOutput_format_name(ImageOutput *imageOutput) {
    return imageOutput->format_name();
}


bool ImageOutput_open (ImageOutput *imageOutput,
                       const char *name, 
                       const ImageSpec *newspec,
                       OpenMode mode) {
    return imageOutput->open(name, *newspec, (ImageOutput::OpenMode)mode);
}


bool ImageOutput_close (ImageOutput *imageOutput) {
    return imageOutput->close();
}

bool ImageOutput_write_image_0 (ImageOutput *imageOutput,
                                enum BaseType format,
                                const void *data) {
    return imageOutput->write_image( TypeDesc( (TypeDesc::BASETYPE) format), 
                                    data);
}

bool ImageOutput_write_image_1 (ImageOutput *imageOutput,
                                enum BaseType format,
                                const void *data,
                                stride_t xstride,
                                stride_t ystride,
                                stride_t zstride,
                                ProgressCallback progress_callback,
                                void *progress_callback_data) {
    
    return imageOutput->write_image(TypeDesc( (TypeDesc::BASETYPE) format), 
                                    data, xstride, ystride, zstride, progress_callback, progress_callback_data);
    
}

bool ImageOutput_write_scanline (ImageOutput *imageOutput,
                                 int y, int z, 
                                 enum BaseType format,
                                 const void *data) {
    
    return imageOutput->write_scanline(y, z, 
                                       TypeDesc( (TypeDesc::BASETYPE) format), 
                                       data);
}

bool ImageOutput_write_scanlines (ImageOutput *imageOutput,
                                  int ybegin, int yend, int z,
                                  enum BaseType format, 
                                  const void *data) {
    
    return imageOutput->write_scanlines(ybegin, yend, z, 
                                        TypeDesc( (TypeDesc::BASETYPE) format), 
                                        data);
}


bool ImageOutput_write_tile (ImageOutput *imageOutput,
                             int x, int y, int z, 
                             enum BaseType format,
                             const void *data) {
    
    return imageOutput->write_tile(x, y, z, TypeDesc( (TypeDesc::BASETYPE) format), data);
}

bool ImageOutput_write_tiles (ImageOutput *imageOutput,
                              int xbegin, int xend, 
                              int ybegin, int yend,
                              int zbegin, int zend, 
                              enum BaseType format,
                              const void *data) {
    
    return imageOutput->write_tiles(xbegin, xend, 
                                    ybegin, yend, 
                                    zbegin, zend,  
                                    TypeDesc( (TypeDesc::BASETYPE) format), 
                                    data);
}

bool ImageOutput_write_rectangle (ImageOutput *imageOutput,
                                  int xbegin, int xend, 
                                  int ybegin, int yend,
                                  int zbegin, int zend, 
                                  enum BaseType format,
                                  const void *data) {
    
    return imageOutput->write_rectangle(xbegin, xend, 
                                        ybegin, yend, 
                                        zbegin, zend, 
                                        TypeDesc( (TypeDesc::BASETYPE) format), 
                                        data);
}


