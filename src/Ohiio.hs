{-# INCLUDE "./ohiio.h" #-}
{-# LINE 1 "src/ohiio-test.hs" #-}
{-# LANGUAGE CPP, ForeignFunctionInterface #-}
{-# LINE 2 "src/ohiio-test.hs" #-}

module Ohiio where

import Foreign
import Foreign.C.Types
import Foreign.C.String
import Data.Word


{-# LINE 11 "src/ohiio-test.hs" #-}

data ImageSpec = ImageSpec
data ImageInput = ImageInput
data ImageOutput = ImageOutput
data TypeDesc = TypeDesc


newtype OpenMode = OpenMode { mode :: CInt }
create  :: OpenMode
create  = OpenMode 0
appendsubimage  :: OpenMode
appendsubimage  = OpenMode 1
appendmiplevel  :: OpenMode
appendmiplevel  = OpenMode 2

{-# LINE 24 "src/ohiio-test.hs" #-}

newtype BaseType = BaseType { btype :: CInt }
unknown  :: BaseType
unknown  = BaseType 0
none  :: BaseType
none  = BaseType 1
uchar  :: BaseType
uchar  = BaseType 2
uint8  :: BaseType
uint8  = BaseType 2
char  :: BaseType
char  = BaseType 3
int8  :: BaseType
int8  = BaseType 3
ushort  :: BaseType
ushort  = BaseType 4
uint16  :: BaseType
uint16  = BaseType 4
short  :: BaseType
short  = BaseType 5
int16  :: BaseType
int16  = BaseType 5
uint  :: BaseType
uint  = BaseType 6
uint32  :: BaseType
uint32  = BaseType 6
int  :: BaseType
int  = BaseType 7
int32  :: BaseType
int32  = BaseType 7
ulonglong  :: BaseType
ulonglong  = BaseType 8
uint64  :: BaseType
uint64  = BaseType 8
longlong  :: BaseType
longlong  = BaseType 9
int64  :: BaseType
int64  = BaseType 9
half  :: BaseType
half  = BaseType 10
float  :: BaseType
float  = BaseType 11
double  :: BaseType
double  = BaseType 12
string  :: BaseType
string  = BaseType 13
ptr  :: BaseType
ptr  = BaseType 14
lastbase  :: BaseType
lastbase  = BaseType 15
 
{-# LINE 52 "src/ohiio-test.hs" #-}

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
