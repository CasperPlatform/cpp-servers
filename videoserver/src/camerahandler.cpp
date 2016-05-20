#include <camerahandler.hpp>

camerahandler::camerahandler()
{
    Camera.setWidth(320);
    Camera.setHeight(240);
    
    //Open camera 
    std::cout << "Opening Camera..." << std::endl;
    if ( !Camera.open()) 
    {
        std::cerr<<"Error opening camera"<<std::endl;
        return;
    }
    
    //wait a while until camera stabilizes
    std::cout<<"Sleeping for 2 secs"<<std::endl;
    
    usleep(2000000);
}

unsigned char* camerahandler::grabImage()
{
    //capture
    Camera.grab();
    
    //allocate memory
    unsigned char *data = new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
    
    //extract the image in rgb format
    Camera.retrieve ( data, raspicam::RASPICAM_FORMAT_RGB );//get camera image
    
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);
    /* Program code to execute here */
     
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
     
    FILE * outfile;		/* target file */
    JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
    int row_stride;		/* physical row width in image buffer */

    cinfo.err = jpeg_std_error(&jerr);
    
    /* Now we can initialize the JPEG compression object. */
    jpeg_create_compress(&cinfo);
    
    unsigned char *mem = NULL;
    unsigned long mem_size = 0;
    
    jpeg_mem_dest(&cinfo, &mem, &mem_size);
    
    cinfo.image_width = Camera.getWidth(); 	/* image width and height, in pixels */
    cinfo.image_height = Camera.getHeight();
    cinfo.input_components = 3;		/* # of color components per pixel */
    cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
    
    jpeg_set_defaults(&cinfo);
    
    jpeg_set_quality(&cinfo, 75, TRUE /* limit to baseline-JPEG values */);

    jpeg_start_compress(&cinfo, TRUE);

    row_stride = Camera.getWidth() * 3;	/* JSAMPLEs per row in image_buffer */

    while (cinfo.next_scanline < cinfo.image_height) 
    {
        /* jpeg_write_scanlines expects an array of pointers to scanlines.
        * Here the array is only one element long, but you could pass
        * more than one scanline at a time if that's more convenient.
        */
        row_pointer[0] = & data[cinfo.next_scanline * row_stride];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    /* After finish_compress, we can close the output file. */
    
    jpeg_destroy_compress(&cinfo);

    delete data;
    
    gettimeofday(&tv2, NULL);
    std::cout << "Image with size: " << mem_size << "created in " << (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec) << " seconds" << std::endl;
    
    struct frame newFrame;
    
    newFrame.size = mem_size;
    newFrame.data = mem;
    
    return newFrame;
}

camerahandler::~camerahandler()
{
    
}