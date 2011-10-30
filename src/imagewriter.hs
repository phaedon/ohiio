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

type Point = (Int, Int)
type Color = (Word8, Word8, Word8, Word8)
type Image = Point -> Color

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

bufferSize :: CInt -> CInt -> CInt -> Int
bufferSize w h ch = fromIntegral (w * h * ch)

mkCInt :: Int -> CInt
mkCInt n = fromIntegral n

imageFn :: (Int, Int) -> Word32
imageFn (x, y) = color
        where
        x10 = even $ x `div` 10
        y10 = even $ y `div` 10
        red = shiftL 255 0
        green = shiftL 255 8
        blue = shiftL 255 16
        black = 0::Word8
        alpha = shiftL 100 24
       
        color = if (x10 && y10) || (not x10 && not y10)
              then red .|. alpha
              else blue .|. green .|. alpha


mkImageFnFromFile :: String -> IO Image
mkImageFnFromFile filename = do

                  -- Read the image and grab the relevant pointers
                  (mem, iSpecPtr) <- readImage filename

                  -- image size info
                  width <- c_ImageSpec_width iSpecPtr 
                  height <- c_ImageSpec_height iSpecPtr 
                  nchannels <- c_ImageSpec_nchannels iSpecPtr                        

                  let dims = (fromIntegral width, fromIntegral height, fromIntegral nchannels)

                  -- Partial function application allows us to return a closure
                  return $ image mem dims
                  
                  where
                  image :: Ptr Word8 -> (Int, Int, Int) -> Image
                  image mem (w, h, chan) (x, y) 
                        -- bounds checking
                        | x >= w = (0,0,0,0)
                        | y >= h = (0,0,0,0)

                        -- We're safe. Retrieve!
                        | otherwise = toColor (unsafePerformIO $ peekByteOff mem offset)

                        where
                        offset = chan * (y * w + x)


poker :: Ptr Word8 -> Image -> (Int, Int) -> (Int, Int) -> IO ()
poker wptr imgFun (xres, _) (x, y) = do
      pokeByteOff wptr (4 * (y * xres + x)) r
      pokeByteOff wptr (4 * (y * xres + x) + 1) g
      pokeByteOff wptr (4 * (y * xres + x) + 2) b
      pokeByteOff wptr (4 * (y * xres + x) + 3) a
       
      where 
      (r, g, b, a) = imgFun (x, y)

initImage :: Ptr Word8 -> Int -> Int -> IO ()
initImage wptr xres yres = do

          genericImage <- mkImageFnFromFile "tanya.png"

          let allCoords = [ (x, y) | x <- [0..xres-1], y <- [0..yres-1] ]
          let myPoker = poker wptr genericImage (xres, yres)
          
          foldr (>>) (return ()) (map myPoker allCoords)


writeImage :: Int -> Int -> String -> IO Bool
writeImage xres yres name = do
           
           -- convert the name to a CString, and take out of IO Monad
           uname <- newCString name
           uempty <- newCString ""
           
           -- allocate some memory
           let memSize = xres * yres * 4
           mem <- mallocBytes memSize

           initImage mem xres yres
           
           -- create an ImageSpec object
           spec <- c_ImageSpecCreate_1 (mkCInt xres) (mkCInt yres) (4::CInt) nullPtr
           
           -- create an ImageOutput object
           outImg <- c_ImageOutputCreate uname uempty

           -- open it in memory...
           openbool <- c_ImageOutput_open outImg uname spec create
           
           -- write the image to file
           writebool <- c_ImageOutput_write_image outImg uint8 mem

           -- close the file
           closebool <- c_ImageOutput_close outImg

           free mem
           free uname
           free uempty
           return (closebool && writebool && openbool)



readImage :: String -> IO (Ptr Word8, Ptr ImageSpec)
readImage name = do
          
          uname <- newCString name
          uempty <- newCString "" 

          -- create a new ImageInput pointer with the filename
          iiPtr <- c_ImageInputCreate uname uempty
          
          -- create a new ImageSpec object
          iSpecPtr <- c_ImageSpecCreate_0 nullPtr          

          -- open the input image, passing again the filename and spec
          isOpen <- c_ImageInput_open iiPtr uname iSpecPtr          

          -- get the xres, yres, and channels from the spec object
          width <- c_ImageSpec_width iSpecPtr
          height <- c_ImageSpec_height iSpecPtr
          nchannels <- c_ImageSpec_nchannels iSpecPtr

          -- use them to create a new memory buffer of type char, xres * yres * channels
          let memSize = bufferSize width height nchannels
          mem <- mallocBytes memSize

          -- call in->read_image(UINT8, pixels)
          isRead <- c_ImageInput_read_image_0 iiPtr uint8 mem

          -- close the input image
          isClosed <- c_ImageInput_close iiPtr

          free uname
          free uempty
          
          -- return the pointer to the data
          return (mem, iSpecPtr)



main :: IO Bool
main = do 

     writeImage 2600 3888 "haskelltest.png" 