/**
* 
*/

#include "src/serialhandler.hpp"
#include "src/SocketTest.h"

int main(){
    
    printf("test\n");
/*
    std::string comPort = "/dev/cu.wchusbserial1420";

    serialhandler sh;


    if(!sh.start(comPort.c_str(), 9600))
    {
        return -1;
    }

    sh.write_string("Bajs\n");

    sleep(5);

    sh.stop();

    */
    SocketTest* socket = new SocketTest();

    socket->startServer("127.0.0.1", "10000");

    return 0;
    
}

