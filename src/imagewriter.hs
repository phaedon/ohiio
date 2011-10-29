import Ohiio

import Foreign.Ptr
import Foreign.C.Types
import Foreign.C.String
import Foreign.Marshal.Alloc
import System.IO.Unsafe

mkCInt :: Int -> CInt
mkCInt n = fromIntegral n

writeImage :: Int -> Int -> String -> IO Bool
writeImage xres yres name = do
           
           -- convert the name to a CString, and take out of IO Monad
           uname <- newCString name
           uempty <- newCString ""
           
           -- allocate some memory
           let memSize = xres * yres * 8 * 3 
           mem <- mallocBytes memSize

           -- create an ImageSpec object
           spec <- return $ c_ImageSpecCreate (mkCInt xres) (mkCInt yres) (3::CInt) nullPtr
           
           -- create an ImageOutput object
           outImg <- return $ c_ImageOutputCreate uname uempty

           -- open it in memory...
           openbool <- return $ c_ImageOutput_open outImg uname spec create
           
           -- write the image to file
           writebool <- return $ c_ImageOutput_write_image outImg uint8 mem

           -- close the file
           closebool <- return $ c_ImageOutput_close outImg

           -- release mem
           free uname
--           free uempty
           free mem
           
           return (closebool && writebool && openbool)