import Ohiio

import Foreign.Ptr
import Foreign.C.Types
import Foreign.C.String
import Foreign.Marshal.Alloc
import Foreign.Storable -- for poking
import Data.Word
import Data.Bits

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


poker :: Ptr Word8 -> ( (Int, Int) -> Word32 ) -> (Int, Int) -> (Int, Int) -> IO ()
poker wptr imgFun (xres, _) (x, y) = 
      pokeByteOff wptr (4 * (y * xres + x)) (imgFun (x, y))


initImage :: Ptr Word8 -> Int -> Int -> IO ()
initImage wptr xres yres = do

          let allCoords = [ (x, y) | x <- [0..xres-1], y <- [0..yres-1] ]
          let myPoker = poker wptr imageFn (xres, yres)
          
          foldr (>>) (return ()) (map myPoker allCoords)


writeImage :: Int -> Int -> String -> IO Bool
writeImage xres yres name = do
           
           -- convert the name to a CString, and take out of IO Monad
           uname <- newCString name
           uempty <- newCString ""
           
           -- allocate some memory
           let memSize = xres * yres * 4
--           mem <- mallocBytes memSize

--           initImage mem xres yres

           mem <- readImage "tanya.png"

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



readImage :: String -> IO (Ptr Word8)
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
          return mem



main :: IO Bool
main = do 

--     mem <- readImage "tanya.png"

     writeImage 2600 3888 "haskelltest.png" 