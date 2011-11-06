-- | Haskell interface to OIIO's ImageOutput functionality
--  (with more of a Haskell flavor)
module Ohiio.ImageOutput where

import OhiioBindings
import Utilities

--import Data.Word
import Foreign.Ptr
import Foreign.C.Types
--import Foreign.Storable -- for poking
import Foreign.C.String -- for newCString
import Foreign.Marshal.Alloc -- for malloc & free

import Foreign.ForeignPtr
import Data.ByteString.Internal (ByteString(..))
import qualified Data.ByteString.Internal as BS


-- TODO: LATER!
--writeImage :: ImageSpec -> 
--writeImage imgSpec name =



-- |Writes an image to file
writeImage :: ByteString -- ^ Initialized mem buffer
           -> (Int, Int) -- ^ Dimensions
           -> String     -- ^ Filename
           -> IO Bool    -- ^ Success?
writeImage imgBuf (xres, yres) name = do

           -- convert the name to a CString, and take out of IO Monad
           uname <- newCString name
           uempty <- newCString ""

           let (mem, _, _) = BS.toForeignPtr imgBuf           
           
           -- create an ImageSpec object
           spec <- c_ImageSpecCreate_1 (mkCInt xres) (mkCInt yres) (4::CInt) nullPtr
           
           -- create an ImageOutput object
           outImg <- c_ImageOutputCreate uname uempty

           -- open it in memory...
           openbool <- c_ImageOutput_open outImg uname spec create
           
           -- write the image to file
           writebool <- withForeignPtr mem (c_ImageOutput_write_image outImg uint8)

           -- close the file
           closebool <- c_ImageOutput_close outImg

           free uname
           free uempty
           return (closebool && writebool && openbool)
