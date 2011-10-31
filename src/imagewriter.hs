import Ohiio

import Foreign.Ptr
import Foreign.C.Types
import Foreign.C.String
import Foreign.Marshal.Alloc
import Foreign.Storable -- for poking
import Data.Word
import Data.Bits
import System.IO.Unsafe


data PrimaryColor = Red | Green | Blue | Alpha
     deriving (Eq, Show)

colorShift :: PrimaryColor -> Int
colorShift pc | pc == Red = 0
              | pc == Green = 8
              | pc == Blue = 16
              | pc == Alpha = 24
              | otherwise = error "No such color!"

colorMask :: PrimaryColor -> Word32
colorMask pc = shiftL 0x000000ff (colorShift pc)

-- converts a hex number to an individual color
getColor :: Word32 -> PrimaryColor -> Word8
getColor wordColor pc = fromIntegral $ shiftR (wordColor .&. mask) sh
         where
         mask = colorMask pc
         sh = colorShift pc



toColor :: Word32 -> Color
toColor wordColor = (gc Red, gc Green, gc Blue, gc Alpha)
        where
        gc = getColor wordColor

fromColor :: Color -> Word32
fromColor (r, g, b, a) = 
          fromIntegral (shiftL r 0)
          .|. fromIntegral (shiftL g 8)
          .|. fromIntegral (shiftL b 16)
          .|. fromIntegral (shiftL a 24)



initImage :: Ptr Word8 -> Int -> Int -> IO ()




main :: IO Bool
main = do 

--     writeImage 2600 3888 "haskelltest.png" 
     writeImage 4000 4000 "haskelltest.png" 