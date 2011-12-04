-- | A friendly Haskell interface to OIIO's ImageSpec struct
module Ohiio.ImageSpec (toHImageSpec, HImageSpec(imgWidth, imgHeight, imgNChannels)) where

import OhiioBindings
import Foreign.Ptr

-- | Haskell version of ImageSpec
data HImageSpec = Spec { 
     imgWidth :: Int,
     imgHeight :: Int,
     imgNChannels :: Int
} deriving (Show, Eq)

toHImageSpec :: Ptr ImageSpec -> IO HImageSpec
toHImageSpec imspec = do
             w <- c_ImageSpec_width imspec
             h <- c_ImageSpec_height imspec
             nch <- c_ImageSpec_nchannels imspec
             let himspec = Spec (fromIntegral w)
                                (fromIntegral h)
                                (fromIntegral nch)
             return himspec
