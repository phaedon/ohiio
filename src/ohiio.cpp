#include "ohiio.h"
#include "imageio.h"
#include "ctypedesc.h"
#include "typedesc.h"
#include "paramlist.h"
#include "cparamlist.h"

    
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
        *qsptr = new QuantizationSpec(_black, _white, _min, _max) ;
        return 0;
    }
    
    int QSpecCreate_1 (QuantizationSpec **qsptr,
                       CTypeDesc *_type) {
        
        *qsptr = new QuantizationSpec( *(TypeDesc *)_type );
        return 0;
    }
    
    
    
    
    /****************************
     *
     *  class ImageSpec
     *
     ****************************/
    
    int ImageSpecCreate_0 (CImageSpec **isptr,
                           CTypeDesc *format) {
        
        *isptr = (CImageSpec *) new ImageSpec( *(TypeDesc *)format);
        return 0;
    }
    
    int ImageSpecCreate_1 (CImageSpec **isptr,
                           int xres, int yres, 
                           int nchans, 
                           CTypeDesc *fmt) {
        
        *isptr = (CImageSpec *) new ImageSpec(xres, yres, nchans, *(TypeDesc *)fmt);
        return 0;
    }
    
    void ImageSpec_set_format (CImageSpec *imageSpec,
                               CTypeDesc *fmt) {
        ((ImageSpec *)imageSpec)->set_format( *(TypeDesc *)fmt);
        
    }
    
    void ImageSpec_default_channel_names (CImageSpec *imageSpec) {
        ((ImageSpec *)imageSpec)->default_channel_names();
    }
    
    
    CTypeDesc *format_from_quantize (CImageSpec *imageSpec,
                                   int quant_black, int quant_white,
                                   int quant_min, int quant_max) {
        
        CTypeDesc *newTypeDesc = (CTypeDesc *)malloc (sizeof(CTypeDesc));
        TypeDesc tDesc = ((ImageSpec *)imageSpec)->format_from_quantize(quant_black, quant_white, quant_min, quant_max);
        memcpy(newTypeDesc, &tDesc, sizeof(TypeDesc));
        return newTypeDesc;
    }
    
    size_t ImageSpec_channel_bytes_0 (const CImageSpec *imageSpec) {
        return ((ImageSpec *)imageSpec)->channel_bytes();
    }
    
    
    size_t ImageSpec_channel_bytes_1 (const CImageSpec *imageSpec,
                                      int chan, bool native) {
        return ((ImageSpec *)imageSpec)->channel_bytes(chan, native);
    }
    
    size_t ImageSpec_pixel_bytes_0 (const CImageSpec *imageSpec,
                                    bool native) {
        return ((ImageSpec *)imageSpec)->pixel_bytes(native);
    }
    
    size_t ImageSpec_pixel_bytes_1 (const CImageSpec *imageSpec,
                                    int firstchan, int nchans, bool native) {
        return ((ImageSpec *)imageSpec)->pixel_bytes(firstchan, nchans, native);
    }
    
    imagesize_t ImageSpec_scanline_bytes (const CImageSpec *imageSpec,
                                          bool native) {
        return ((ImageSpec *)imageSpec)->scanline_bytes(native);
    }
    
    imagesize_t ImageSpec_tile_pixels (const CImageSpec *imageSpec) {
        return ((ImageSpec *)imageSpec)->tile_pixels();
    }
    
    imagesize_t ImageSpec_tile_bytes (const CImageSpec *imageSpec,
                                      bool native) {
        return ((ImageSpec *)imageSpec)->tile_bytes(native);
    }
    
    imagesize_t ImageSpec_image_pixels (const CImageSpec *imageSpec) {
        return ((ImageSpec *)imageSpec)->image_pixels();
    }
    
    imagesize_t ImageSpec_image_bytes (const CImageSpec *imageSpec,
                                       bool native) {
        return ((ImageSpec *)imageSpec)->image_bytes(native);
    }
    
    bool ImageSpec_size_t_safe(const CImageSpec *imageSpec) {
        return ((ImageSpec *)imageSpec)->size_t_safe();
    }
    
    
    void ImageSpec_auto_stride_0 (CImageSpec *imageSpec,
                                  stride_t *xstride, stride_t *ystride,
                                  stride_t *zstride, stride_t channelsize,
                                  int nchannels, int width, int height) {
        ((ImageSpec *)imageSpec)->auto_stride(*xstride, *ystride, *zstride, channelsize, nchannels, width, height);
    }
    
    void ImageSpec_auto_stride_1 (CImageSpec *imageSpec,
                                  stride_t *xstride, stride_t *ystride,
                                  stride_t *zstride, CTypeDesc *format,
                                  int nchannels, int width, int height) {
        ((ImageSpec *)imageSpec)->auto_stride(*xstride, *ystride, *zstride, *(TypeDesc *)format, nchannels, width, height);
    }
    
    void ImageSpec_auto_stride_2 (CImageSpec *imageSpec,
                                  stride_t *xstride, CTypeDesc *format, int nchannels) {
        ((ImageSpec *)imageSpec)->auto_stride(*xstride, *(TypeDesc *)format, nchannels);
    }
    
    void ImageSpec_attribute_0 (CImageSpec *imageSpec,
                                const char *name, CTypeDesc *type, const void *value) {
        ((ImageSpec *)imageSpec)->attribute(name, *(TypeDesc *)type, value);
    }
    
    void ImageSpec_attribute_1 (CImageSpec *imageSpec,
                                const char *name, CTypeDesc *type, const char *value) {
        ((ImageSpec *)imageSpec)->attribute(name, *(TypeDesc *)type, value);
    }
    
    void ImageSpec_attribute_2 (CImageSpec *imageSpec,
                                const char *name, unsigned int value) {
        ((ImageSpec *)imageSpec)->attribute(name, value);
    }
    
    void ImageSpec_attribute_3 (CImageSpec *imageSpec,
                                const char *name, int value) {
        ((ImageSpec *)imageSpec)->attribute(name, value);
    }
    
    void ImageSpec_attribute_4 (CImageSpec *imageSpec,
                                const char *name, float value) {
        ((ImageSpec *)imageSpec)->attribute(name, value);
    }
    
    void ImageSpec_attribute_5 (CImageSpec *imageSpec,
                                const char *name, const char *value) {
        ((ImageSpec *)imageSpec)->attribute(name, value);
    }
    
    void ImageSpec_attribute_6 (CImageSpec *imageSpec,
                                const char *name, const char *value) {
        ((ImageSpec *)imageSpec)->attribute(name, value);
    }
    
    void ImageSpec_erase_attribute (CImageSpec *imageSpec,
                                    const char *name,
                                    CTypeDesc *searchtype,
                                    bool casesensitive) {
        ((ImageSpec *)imageSpec)->erase_attribute(name, *(TypeDesc *)searchtype, casesensitive);
    }
    
 /*   CImageIOParameter * find_attribute (CImageSpec *imageSpec,
                                       const char *name,
                                       CTypeDesc *searchtype,
                                       bool casesensitive) {
        
        
        
        return ((ImageSpec *)imageSpec)->find_attribute(name, *(TypeDesc *)searchtype, casesensitive);
    }
    
    const CImageIOParameter *ImageSpec_find_attribute (const CImageSpec *imageSpec,
                                                      const char *name,
                                                      CTypeDesc *searchtype,
                                                      bool casesensitive) {
        return ((ImageSpec *)imageSpec)->find_attribute(name, searchtype, casesensitive);
    }
    */
    
    int ImageSpec_get_int_attribute (const CImageSpec *imageSpec,
                                     const char *name, int defaultval) {
        return ((ImageSpec *)imageSpec)->get_int_attribute(name, defaultval);
    }
    
    float ImageSpec_get_float_attribute (const CImageSpec *imageSpec,
                                         const char *name,
                                         float defaultval) {
        return ((ImageSpec *)imageSpec)->get_float_attribute(name, defaultval);
    }
    
    const char * ImageSpec_get_string_attribute (const CImageSpec *imageSpec,
                                                 const char *name,
                                                 const char *defaultval) {
        return ((ImageSpec *)imageSpec)->get_string_attribute(name, defaultval).c_str();
    }
    
    const char * ImageSpec_metadata_val (const CImageSpec *imageSpec,
                                         const CImageIOParameter *p,
                                         bool human) {
        return ((ImageSpec *)imageSpec)->metadata_val(*(ImageIOParameter*)p, human).c_str();
    }
    
    const char * ImageSpec_to_xml (const CImageSpec *imageSpec) {
        return ((ImageSpec *)imageSpec)->to_xml().c_str();
    }
    
    void ImageSpec_from_xml (CImageSpec *imageSpec,
                             const char *xml) {
        ((ImageSpec *)imageSpec)->from_xml(xml);
    }
    
    bool ImageSpec_valid_tile_range (CImageSpec *imageSpec,
                                     int xbegin, int xend, int ybegin, int yend,
                                     int zbegin, int zend) {
        return ((ImageSpec *)imageSpec)->valid_tile_range(xbegin, xend, ybegin, yend, zbegin, zend);
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
                           const CImageSpec *newspec,
                           COpenMode mode) {
        return imageOutput->open(name, *(ImageSpec*)newspec, (ImageOutput::OpenMode)mode);
    }
    
    
    
//}


