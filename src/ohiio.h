/**
 * ohiio -- C-compatible wrappers for the C++ classes in OIIO
 * ================
 * Phaedon Sinis
 * October 2011
 */


#ifndef __OHIIO_H__
#define __OHIIO_H__


#ifdef __cplusplus

    #include "imageio.h"
    OIIO_NAMESPACE_USING
    //using namespace OpenImageIO;

#else
    
    #include <stddef.h> // to get ptrdiff_t
    #include <stdbool.h> // bool type
    typedef struct TypeDesc TypeDesc;
    typedef struct ImageSpec ImageSpec;
    typedef struct ImageInput ImageInput;
    typedef struct ImageOutput ImageOutput;
    //typedef struct QuantizationSpec QuantizationSpec;

    typedef ptrdiff_t stride_t;

/// Type we use to express how many pixels (or bytes) constitute an image,
/// tile, or scanline.  Needs to be large enough to handle very big images
/// (which we presume could be > 4GB).
#if defined(LINUX64) /* add others if we know for sure size_t is ok */
typedef size_t imagesize_t;
#else
typedef unsigned long long imagesize_t;
#endif // end LINUX64

#endif // end CPLUSPLUS

enum OpenMode { Create, AppendSubimage, AppendMIPLevel };




#ifdef __cplusplus 
extern "C" {
#endif
    
    
    /****************************
     *
     *  class ImageSpec
     *
     ****************************/
    
    /// Constructor: given just the data format, set the default quantize
    /// and set all other channels to something reasonable.
    ImageSpec *ImageSpecCreate_0 (TypeDesc *format);
    
    /// Constructor for simple 2D scanline image with nothing special.
    /// If fmt is not supplied, default to unsigned 8-bit data.
    ImageSpec *ImageSpecCreate_1 (int xres, int yres, int nchans, 
                          TypeDesc *fmt);
    
    
    /****************************
     *
     *  class ImageInput
     *
     ****************************/
    
    void ImageInputCreate (ImageInput **iiptr,
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
    
    void ImageOutputCreate (ImageOutput **ioptr,
                            const char *filename,
                            const char *plugin_searchpath);
        
    bool ImageOutput_open (ImageOutput *imageOutput,
                           const char *name, 
                           const ImageSpec *newspec,
                           enum OpenMode mode);
#ifdef __cplusplus   
}
#endif


#endif
