-- | Haskell interface to OIIO's ImageOutput functionality
--  (with more of a Haskell flavor)
module Ohiio.ImageOutput (writeImage) where

import OhiioBindings
import Utilities

import Data.Word
import Foreign.Ptr
import Foreign.C.Types
import Foreign.Marshal.Alloc -- for malloc & free
import Foreign.Storable -- for poking
import Foreign.C.String -- for newCString

-- TODO: LATER!
--writeImage :: ImageSpec -> 
--writeImage imgSpec name =

-- TODO: import the definitions from HIP... argh. circular
type Point2D = (Int, Int)
type RGBAColor = (Word8, Word8, Word8, Word8)
type Image = Point2D -> RGBAColor

-- |Modifies a 32-bit word in a memory buffer, 
-- based on a 2D interpretation of the space.
-- Color comes from provided image function.
poker :: BytePtr -> Image -> (Int, Int) -> (Int, Int) -> IO ()
poker wptr imgFun (xres, _) (x, y) = do
      pokeByteOff wptr (4 * (y * xres + x)) r
      pokeByteOff wptr (4 * (y * xres + x) + 1) g
      pokeByteOff wptr (4 * (y * xres + x) + 2) b
      pokeByteOff wptr (4 * (y * xres + x) + 3) a
       
      where 
      (r, g, b, a) = imgFun (x, y)


populateBuffer :: BytePtr -> Image -> (Int, Int) -> IO ()
populateBuffer wptr img (xres, yres) = do 

               -- define double loop over monadic actions
               let loop i j | j == yres = return ()
                            | i == xres = loop 0 (j+1)
                            | otherwise = 
                     poker wptr img (xres, yres) (i,j) >> loop (i+1) j

               loop 0 0

-- |Writes an image to file
writeImage :: Image      -- ^ Image function to output
           -> (Int, Int) -- ^ Dimensions
           -> String     -- ^ Filename
           -> IO Bool    -- ^ Success?
writeImage img (xres, yres) name = do
           
           -- convert the name to a CString, and take out of IO Monad
           uname <- newCString name
           uempty <- newCString ""
           
           -- allocate some memory
           let memSize = xres * yres * 4
           mem <- mallocBytes memSize

           populateBuffer mem img (xres, yres)
           
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
