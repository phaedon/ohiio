module Utilities where

import Foreign.C.Types

bufferSize :: CInt -> CInt -> CInt -> Int
bufferSize w h ch = fromIntegral (w * h * ch)

mkCInt :: Int -> CInt
mkCInt n = fromIntegral n
