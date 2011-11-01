-- | This is a friendly Haskell interface to OIIO's ImageInput struct.
module Ohiio.ImageInput (readImage) where

import OhiioBindings
import Utilities

import Data.Word
import Foreign.Ptr
import Foreign.C.String -- for newCString
import Foreign.Marshal.Alloc -- for malloc & free

-- |Reads an image from file.
-- The "name" argument is the filename.
-- Returns a pair. The first element is a pointer to the 
-- image memory buffer; the second element is a pointer 
-- to the image's metadata.
readImage :: String  -- ^ Filename
          -> IO (Ptr Word8, Ptr ImageSpec) -- ^ The first elem is a pointer to 
                            -- the image memory buffer, and the second is a 
                            -- pointer to the image's metadata
readImage name = do
          
          uname <- newCString name
          uempty <- newCString "" 

          -- create a new ImageInput pointer with the filename
          iiPtr <- c_ImageInputCreate uname uempty
          
          -- create a new ImageSpec object
          iSpecPtr <- c_ImageSpecCreate_0 nullPtr          

          -- open the input image, passing again the filename and spec
          isOpen <- c_ImageInput_open iiPtr uname iSpecPtr          
          if not isOpen
             then error "Could not open the input image."
             else do

             -- get the xres, yres, and channels from the spec object
             width <- c_ImageSpec_width iSpecPtr
             height <- c_ImageSpec_height iSpecPtr
             nchannels <- c_ImageSpec_nchannels iSpecPtr

             -- use them to create a new memory buffer of type char, xres * yres * channels
             let memSize = bufferSize width height nchannels
             mem <- mallocBytes memSize

             -- call in->read_image(UINT8, pixels)
             isRead <- c_ImageInput_read_image_0 iiPtr uint8 mem
             if not isRead
                then do free mem
                        free uname
                        free uempty
                        error "Could not read the input image."  
                else do

                -- close the input image
                isClosed <- c_ImageInput_close iiPtr
                if not isClosed 
                   then error "Could not close the output image."
                   else do 
                   free uname
                   free uempty
  
                   -- return the pointer to the data
                   return (mem, iSpecPtr)

