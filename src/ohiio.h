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
    using namespace OpenImageIO;
#else
    #include "stddef.h"
    #include <stdbool.h>
    typedef struct ImageInput ImageInput;
    typedef struct ImageOutput ImageOutput;
    typedef struct QuantizationSpec QuantizationSpec;
#endif


struct CParamValue;

typedef ptrdiff_t stride_t;
typedef struct CParamValue CImageIOParameter;

enum COpenMode { Create, AppendSubimage, AppendMIPLevel };

/// Type we use to express how many pixels (or bytes) constitute an image,
/// tile, or scanline.  Needs to be large enough to handle very big images
/// (which we presume could be > 4GB).
#if defined(LINUX64) /* add others if we know for sure size_t is ok */
typedef size_t imagesize_t;
#else
typedef unsigned long long imagesize_t;
#endif

struct CTypeDesc;

struct CImageSpec;


#ifdef __cplusplus 
extern "C" {
#endif
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
    
    int QSpecCreate_1 (QuantizationSpec **qsptr, struct CTypeDesc *_type);
    
  
    
    /****************************
     *
     *  class ImageSpec
     *
     ****************************/
    
    /// Constructor: given just the data format, set the default quantize
    /// and set all other channels to something reasonable.
    int ImageSpecCreate_0 (struct CImageSpec **isptr,
                           struct CTypeDesc *format);

    /// Constructor for simple 2D scanline image with nothing special.
    /// If fmt is not supplied, default to unsigned 8-bit data.
    int ImageSpecCreate_1 (struct CImageSpec **isptr,
                           int xres, int yres, 
                           int nchans, 
                           struct CTypeDesc *fmt);
    
    /// Set the data format, and as a side effect set quantize
    /// to good defaults for that format
    void ImageSpec_set_format (struct CImageSpec *imageSpec, 
                               struct CTypeDesc *fmt);
    
    /// Set the channelnames to reasonable defaults ("R", "G", "B", "A"),
    /// and alpha_channel, based on the number of channels.
    void ImageSpec_default_channel_names (struct CImageSpec *imageSpec);
    
    /// Given quantization parameters, deduce a TypeDesc that can
    /// be used without unacceptable loss of significant bits.
    struct CTypeDesc *format_from_quantize (struct CImageSpec *imageSpec,
                                   int quant_black, int quant_white,
                                   int quant_min, int quant_max);
    
    size_t ImageSpec_channel_bytes_0 (const struct CImageSpec *imageSpec);
    
    size_t ImageSpec_channel_bytes_1 (const struct CImageSpec *imageSpec,
                                      int chan, bool native);
    
    size_t ImageSpec_pixel_bytes_0 (const struct CImageSpec *imageSpec, bool native);
    
    size_t ImageSpec_pixel_bytes_1 (const struct CImageSpec *imageSpec,
                                    int firstchan, int nchans, bool native);
    
    imagesize_t ImageSpec_scanline_bytes (const struct CImageSpec *imageSpec, bool native);
    
    imagesize_t ImageSpec_tile_pixels (const struct CImageSpec *imageSpec);
    
    imagesize_t ImageSpec_tile_bytes (const struct CImageSpec *imageSpec, bool native);
    
    imagesize_t ImageSpec_image_pixels (const struct CImageSpec *imageSpec);
    
    imagesize_t ImageSpec_image_bytes (const struct CImageSpec *imageSpec, bool native);
    
    bool ImageSpec_size_t_safe(const struct CImageSpec *imageSpec);

    void ImageSpec_auto_stride_0 (struct CImageSpec *imageSpec,
                                  stride_t *xstride, stride_t *ystride,
                             stride_t *zstride, stride_t channelsize,
                             int nchannels, int width, int height);
    
    void ImageSpec_auto_stride_1 (struct CImageSpec *imageSpec,
                                  stride_t *xstride, stride_t *ystride,
                                  stride_t *zstride, 
                                  struct CTypeDesc *format,
                                  int nchannels, 
                                  int width, 
                                  int height);
    
    void ImageSpec_auto_stride_2 (struct CImageSpec *imageSpec,
                                  stride_t *xstride, 
                                  struct CTypeDesc *format, 
                                  int nchannels);
    
    void ImageSpec_attribute_0 (struct CImageSpec *imageSpec,
                                const char *name, 
                                struct CTypeDesc *type, 
                                const void *value);
    
    void ImageSpec_attribute_1 (struct CImageSpec *imageSpec,
                                const char *name, 
                                struct CTypeDesc *type, 
                                const char *value);
    
    void ImageSpec_attribute_2 (struct CImageSpec *imageSpec,
                                const char *name, unsigned int value);
    
    void ImageSpec_attribute_3 (struct CImageSpec *imageSpec,
                                const char *name, int value);
    
    void ImageSpec_attribute_4 (struct CImageSpec *imageSpec,
                                const char *name, float value);
    
    void ImageSpec_attribute_5 (struct CImageSpec *imageSpec,
                                const char *name, const char *value);
    
    void ImageSpec_attribute_6 (struct CImageSpec *imageSpec,
                                const char *name, const char *value);
    
    void ImageSpec_erase_attribute (struct CImageSpec *imageSpec,
                                    const char *name,
                                    struct CTypeDesc *searchtype,
                                    bool casesensitive);
/*
    CImageIOParameter *find_attribute (CImageSpec *imageSpec,
                                       const char *name,
                                       CTypeDesc *searchtype,
                                       bool casesensitive = false);
    
    const CImageIOParameter *ImageSpec_find_attribute (const CImageSpec *imageSpec,
                                                      const char *name,
                                                       CTypeDesc *searchtype,
                                                       bool casesensitive=false);
  */
    
    
    int ImageSpec_get_int_attribute (const struct  CImageSpec *imageSpec,
                                     const char *name, int defaultval);
    
    float ImageSpec_get_float_attribute (const struct CImageSpec *imageSpec,
                                         const char *name,
                                         float defaultval);
    
    const char * ImageSpec_get_string_attribute (const struct CImageSpec *imageSpec,
                                                 const char *name,
                                                 const char *defaultval);

    const char * ImageSpec_metadata_val (const struct CImageSpec *imageSpec,
                                         const CImageIOParameter *p,
                                         bool human);
    
    const char * ImageSpec_to_xml (const struct CImageSpec *imageSpec);

    void ImageSpec_from_xml (struct CImageSpec *imageSpec,
                             const char *xml);
    
    bool ImageSpec_valid_tile_range (struct CImageSpec *imageSpec,
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
    
    void ImageOutputCreate (ImageOutput **ioptr,
                            const char *filename,
                            const char *plugin_searchpath);
        
    bool ImageOutput_open (ImageOutput *imageOutput,
                           const char *name, 
                           const struct CImageSpec *newspec,
                           enum COpenMode mode);
#ifdef __cplusplus   
}
#endif


#endif
