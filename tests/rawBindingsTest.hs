import OhiioBindings
--import Utilities

--import Data.Word
import Foreign.Ptr
import Foreign.C.Types
--import Foreign.Storable -- for poking
import Foreign.C.String -- for newCString
import Foreign.Marshal.Alloc -- for malloc & free
import Foreign.ForeignPtr

-- |Computes required buffer size (in bytes) 
-- given a width, height, and number of channels
bufferSize :: CInt -> CInt -> CInt -> Int
bufferSize w h ch = fromIntegral (w * h * ch)


testFullImage name ext path = do
              uname <- newCString (name ++ ext)
              upath <- newCString path

              -- create a new ImageInput pointer
              iiPtr <- c_ImageInputCreate uname upath

              -- create a new ImageSpec object
              iSpecPtr <- c_ImageSpecCreate_0 nullPtr

              _ <- c_ImageInput_open iiPtr uname iSpecPtr


              -- oh well, we're responsible for alloc'ing the memory
              -- get the xres, yres, and channels from the spec object
              width <- c_ImageSpec_width iSpecPtr
              height <- c_ImageSpec_height iSpecPtr
              nchannels <- c_ImageSpec_nchannels iSpecPtr

              -- use them to create a new memory buffer of type char, xres * yres * channels
              let memSize = bufferSize width height nchannels
              mem <- mallocBytes memSize

              -- Read into the buffer!
              isRead <- c_ImageInput_read_image_0 iiPtr uint8 mem

              let outputName = "output_" ++ name ++ ext
              oname <- newCString outputName
              -- TODO: also change the path
              ioPtr <- c_ImageOutputCreate oname upath
              
              _ <- c_ImageOutput_open ioPtr oname iSpecPtr create
              _ <- c_ImageOutput_write_image ioPtr uint8 mem

              -- Convert to a JPEG
              jpgName <- newCString ("output_" ++ name ++ ".jpg")
              ioJPEGPtr <- c_ImageOutputCreate jpgName upath
              _ <- c_ImageOutput_open ioJPEGPtr jpgName iSpecPtr create
              _ <- c_ImageOutput_write_image ioJPEGPtr uint8 mem
              
              -- be nice
              _ <- c_ImageInput_close iiPtr
              _ <- c_ImageOutput_close ioPtr
              _ <- c_ImageOutput_close ioJPEGPtr

              -- free the mem
              free mem
              
main = do
     testFullImage "lambros" ".png" ""
     testFullImage "tanya" ".png" ""