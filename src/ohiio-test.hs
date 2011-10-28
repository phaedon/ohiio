{-# LANGUAGE CPP, ForeignFunctionInterface #-}

module Ohiio where

import Foreign
import Foreign.C.Types

#include "./ohiio.h"

data ImageSpec
data TypeDesc

foreign import ccall "ImageSpecCreate_1"
        c_ImageSpecCreate :: CInt -> CInt -> CInt -> Ptr TypeDesc -> Ptr ImageSpec
        