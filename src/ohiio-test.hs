{-# LANGUAGE CPP, ForeignFunctionInterface #-}

module Ohiio where

import Foreign
import Foreign.C.Types
import Foreign.C.String
import Data.Word

#include "./ohiio.h"

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

foreign import ccall "ImageSpecCreate_1"
        c_ImageSpecCreate :: CInt -> CInt -> CInt -> Ptr TypeDesc -> IO (Ptr ImageSpec)



foreign import ccall "ImageOutputCreate"
--        c_ImageOutputCreate :: Ptr CChar -> Ptr CChar -> Ptr ImageOutput
        c_ImageOutputCreate :: CString -> CString -> IO (Ptr ImageOutput)

foreign import ccall unsafe "ImageOutput_open"
        c_ImageOutput_open :: Ptr ImageOutput -> Ptr CChar -> Ptr ImageSpec -> OpenMode -> IO Bool

foreign import ccall unsafe "ImageOutput_close"
        c_ImageOutput_close :: Ptr ImageOutput -> IO Bool

foreign import ccall unsafe "ImageOutput_write_image_0"
        c_ImageOutput_write_image :: Ptr ImageOutput -> BaseType -> Ptr Word8 -> IO Bool
