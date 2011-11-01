-- | A few convenient utilities involving memory management 
--   and type conversions.
module Utilities where

import Foreign.C.Types

-- |Computes required buffer size (in bytes) 
-- given a width, height, and number of channels
bufferSize :: CInt -> CInt -> CInt -> Int
bufferSize w h ch = fromIntegral (w * h * ch)

-- |Converts an Int to a CInt
mkCInt :: Int -> CInt
mkCInt = fromIntegral
