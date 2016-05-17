#ifndef camera_handler_hpp
#define camera_handler_hpp

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "jpeglib.h"
#include <setjmp.h>
#include <raspicam/raspicam.h>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <sys/time.h>

class camerahandler
{
    public:
        camerahandler();
        ~camerahandler();
        
        char* grabImage();
    private:
        
};

#endif // camera_handler_hpp