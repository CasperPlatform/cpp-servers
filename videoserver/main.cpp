#include <videoserver.hpp>
#include <camerahandler.hpp>
#include <sockethandler.hpp>
#include <stdio.h>
#include <iostream>

int main()
{
    printf("Running main.\n");  
    
    camerahandler camera;
    
    /*try
    {
        sockethandler server(6000);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    printf("Waiting for message.");
    
    */
    printf("Stopping main.\n");  

    return 0; 
}