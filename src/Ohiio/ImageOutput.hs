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

               let allCoords = [ (x, y) | x <- [0..xres-1], y <- [0..yres-1] ]
               let myPoker = poker wptr img (xres, yres)
          
               --  foldr (>>) (return ()) (map myPoker allCoords)
               mapM_ myPoker allCoords


writeImage :: Image -> (Int, Int) -> String -> IO Bool
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
