{-# LANGUAGE CPP, ForeignFunctionInterface #-}

module OhiioBindings where

import Foreign
import Foreign.C.Types
import Foreign.C.String
--import Foreign.ForeignPtr

#include "./ohiio.h"

type BytePtr = Ptr Word8

data ImageSpec = ImageSpec
data ImageInput = ImageInput
data ImageOutput = ImageOutput
data TypeDesc = TypeDesc


newtype OpenMode = OpenMode { mode :: CInt }
#{enum OpenMode, OpenMode,
       create = Create, 
       appendsubimage = AppendSubimage, 
       appendmiplevel = AppendMIPLevel 
}

newtype BaseType = BaseType { btype :: CInt }
#{enum BaseType, BaseType,
     unknown = UNKNOWN,
     none = NONE,
     uchar =  UCHAR,
     uint8 = UCHAR,
     char = CHAR,
     int8 = INT8,
     ushort = USHORT,
     uint16 = UINT16,
     short = SHORT,
     int16 = INT16,
     uint = UINT,
     uint32 = UINT32,
     int = INT,
     int32 = INT32,
     ulonglong = ULONGLONG,
     uint64 = UINT64,
     longlong = LONGLONG,
     int64 = INT64,
     half = HALF,
     float = FLOAT,
     double = DOUBLE,
     string = STRING,
     ptr = PTR,
     lastbase = LASTBASE
} 


{-
 class ImageSpec
-}

foreign import ccall unsafe "ImageSpecCreate_0"
        c_ImageSpecCreate_0 :: Ptr TypeDesc -> IO (Ptr ImageSpec)

foreign import ccall unsafe "ImageSpecCreate_1"
        c_ImageSpecCreate_1 :: CInt -> CInt -> CInt -> Ptr TypeDesc -> IO (Ptr ImageSpec)

foreign import ccall unsafe "ImageSpec_width"
        c_ImageSpec_width :: Ptr ImageSpec -> IO CInt

foreign import ccall unsafe "ImageSpec_height"
        c_ImageSpec_height :: Ptr ImageSpec -> IO CInt

foreign import ccall unsafe "ImageSpec_nchannels"
        c_ImageSpec_nchannels :: Ptr ImageSpec -> IO CInt


{-
 class ImageInput
-}

foreign import ccall unsafe "ImageInputCreate"
        c_ImageInputCreate :: CString -> CString -> IO (Ptr ImageInput)

foreign import ccall unsafe "ImageInput_open"
        c_ImageInput_open :: Ptr ImageInput -> CString -> Ptr ImageSpec -> IO Bool

foreign import ccall unsafe "ImageInput_close"
        c_ImageInput_close :: Ptr ImageInput -> IO Bool

foreign import ccall unsafe "ImageInput_read_image_0"
        c_ImageInput_read_image_0 :: Ptr ImageInput -> BaseType -> Ptr Word8 -> IO Bool

foreign import ccall unsafe "ImageInput_read_image_1"
        c_ImageInput_read_image_1 :: Ptr ImageInput -> Ptr Float -> IO Bool


{-
 class ImageOutput
-}


foreign import ccall unsafe "ImageOutputCreate"
        c_ImageOutputCreate :: CString -> CString -> IO (Ptr ImageOutput)

foreign import ccall unsafe "ImageOutput_format_name"
        c_ImageOutput_format_name :: Ptr ImageOutput -> IO Bool

foreign import ccall unsafe "ImageOutput_open"
        c_ImageOutput_open :: Ptr ImageOutput -> Ptr CChar -> Ptr ImageSpec -> OpenMode -> IO Bool

foreign import ccall unsafe "ImageOutput_close"
        c_ImageOutput_close :: Ptr ImageOutput -> IO Bool

foreign import ccall unsafe "ImageOutput_write_image_0"
        c_ImageOutput_write_image :: Ptr ImageOutput -> BaseType -> Ptr Word8 -> IO Bool

foreign import ccall unsafe "ImageOutput_write_scanline"
        c_ImageOutput_write_scanline :: Ptr ImageOutput -> CInt -> CInt -> BaseType -> Ptr Word8 -> IO Bool

foreign import ccall unsafe "ImageOutput_write_scanlines"
        c_ImageOutput_write_scanlines :: Ptr ImageOutput -> CInt -> CInt -> CInt 
                                         -> BaseType -> Ptr Word8 -> IO Bool

foreign import ccall unsafe "ImageOutput_write_tile"
        c_ImageOutput_write_tile :: Ptr ImageOutput 
                                    -> CInt -> CInt -> CInt
                                    -> BaseType -> Ptr Word8 -> IO Bool

foreign import ccall unsafe "ImageOutput_write_tiles"
        c_ImageOutput_write_tiles :: Ptr ImageOutput 
                                    -> CInt -> CInt 
                                    -> CInt -> CInt
                                    -> CInt -> CInt
                                    -> BaseType -> Ptr Word8 -> IO Bool

foreign import ccall unsafe "ImageOutput_write_rectangle"
        c_ImageOutput_write_rectangle :: Ptr ImageOutput 
                                    -> CInt -> CInt 
                                    -> CInt -> CInt
                                    -> CInt -> CInt
                                    -> BaseType -> Ptr Word8 -> IO Bool
