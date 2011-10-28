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
    

    /****************************
     *
     *  class ImageInput
     *
     ****************************/
    
    
    void ImageInputCreate (ImageInput **iiptr,
                          char *filename,
                          char *plugin_searchpath) {
        *iiptr = ImageInput::create(filename, plugin_searchpath);
    }
    
    
    bool ImageInput_read_scanline (ImageInput *imageInput,
                                   int y, 
                                   int z, 
                                   float *data) {
        
        return imageInput->read_scanline (y, z, TypeDesc::FLOAT, data);
        
    }
    
    bool ImageInput_read_image (ImageInput *imageInput, 
                                float *data) {
        return imageInput->read_image (TypeDesc::FLOAT, data);
    }
    
    
    
    /****************************
     *
     *  class ImageOutput
     *
     ****************************/

    void ImageOutputCreate (ImageOutput **ioptr,
                              const char *filename,
                              const char *plugin_searchpath) {
        if (plugin_searchpath == NULL) {
            *ioptr = ImageOutput::create(filename, plugin_searchpath);
        } else {
            *ioptr = ImageOutput::create(filename, "");
        }

    }

    
    bool ImageOutput_open (ImageOutput *imageOutput,
                           const char *name, 
                           const ImageSpec *newspec,
                           OpenMode mode) {
        return imageOutput->open(name, *newspec, (ImageOutput::OpenMode)mode);
    }
    
    
    
//}


