-- {-# INCLUDE "./ohiio.h" #-}
{-# LINE 1 "src/bindings.hs" #-}
{-# LANGUAGE CPP, ForeignFunctionInterface #-}
{-# LINE 2 "src/bindings.hs" #-}

module OhiioBindings where

import Foreign
import Foreign.C.Types
import Foreign.C.String


{-# LINE 10 "src/bindings.hs" #-}

type BytePtr = Ptr Word8

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

{-# LINE 25 "src/bindings.hs" #-}

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
 
{-# LINE 53 "src/bindings.hs" #-}


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

foreign import ccall unsafe "ImageOutput_open"
        c_ImageOutput_open :: Ptr ImageOutput -> Ptr CChar -> Ptr ImageSpec -> OpenMode -> IO Bool

foreign import ccall unsafe "ImageOutput_close"
        c_ImageOutput_close :: Ptr ImageOutput -> IO Bool

foreign import ccall unsafe "ImageOutput_write_image_0"
        c_ImageOutput_write_image :: Ptr ImageOutput -> BaseType -> Ptr Word8 -> IO Bool
