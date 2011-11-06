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
    typedef bool (*ProgressCallback)(void *opaque_data, float portion_done);


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
enum BaseType { UNKNOWN, NONE, 
    UCHAR, UINT8=UCHAR, CHAR, INT8=CHAR,
    USHORT, UINT16=USHORT, SHORT, INT16=SHORT,
    UINT, UINT32=UINT, INT, INT32=INT,
    ULONGLONG, UINT64=ULONGLONG, LONGLONG, INT64=LONGLONG,
    HALF, FLOAT, DOUBLE, STRING, PTR, LASTBASE };

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
    
    int ImageSpec_width(ImageSpec *ispec);
    int ImageSpec_height(ImageSpec *ispec);
    int ImageSpec_nchannels(ImageSpec *ispec);
    
    /****************************
     *
     *  class ImageInput
     *
     ****************************/
    
    ImageInput *ImageInputCreate (const char *filename,
                                  const char *plugin_searchpath);

    
    /// Open file with given name.  Various file attributes are put in
    /// newspec and a copy is also saved in this->spec.  From these
    /// attributes, you can discern the resolution, if it's tiled,
    /// number of channels, and native data format.  Return true if the
    /// file was found and opened okay.
    bool ImageInput_open (ImageInput *imageInput,
                          const char *name, ImageSpec *newspec);

    bool ImageInput_close (ImageInput *imageInput);
    
    bool ImageInput_read_image_0 (ImageInput *imageInput, 
                                  enum BaseType format,
                                  void *data);
    
    /// Simple read_image reads to contiguous float pixels.
    bool ImageInput_read_image_1 (ImageInput *imageInput, 
                                float *data);
    
    
    /****************************
     *
     *  class ImageOutput
     *
     ****************************/
    
    ImageOutput *ImageOutputCreate (const char *filename,
                                    const char *plugin_searchpath);
        
    bool ImageOutput_open (ImageOutput *imageOutput,
                           const char *name, 
                           const ImageSpec *newspec,
                           enum OpenMode mode);
    
    bool ImageOutput_close (ImageOutput *imageOutput);
    
    // uses default args
    bool ImageOutput_write_image_0 (ImageOutput *imageOutput,
                                    enum BaseType basetype,
                                    const void *data);
    
    bool ImageOutput_write_image_1 (ImageOutput *imageOutput,
                                    enum BaseType basetype,
                                    const void *data,
                                    stride_t xstride,
                                    stride_t ystride,
                                    stride_t zstride,
                                    ProgressCallback progress_callback,
                                    void *progress_callback_data);
    
#ifdef __cplusplus   
}
#endif


#endif
