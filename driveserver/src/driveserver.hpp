/**
*	Casper drive_server Header 
*	Author @Pontus Pohl and @Linus Eiderström Swahn
*/
#ifndef drive_server_h
#define drive_server_h

#include <ostream>
#include <iostream>
#include <string>
#include <serialhandler.hpp>
#include <SocketHandler.hpp>
#include "sqlite3.h"
// flag defs
#define DRIVE_FLAG 0x44
#define BACKWARD_FLAG 0x42
#define FORWARD_FLAG 0x46
#define RIGHT_ANGLE_FLAG 0x52
#define LEFT_ANGLE_FLAG 0x4c
#define IDLE_DRIVE_FLAG 0x49

typedef boost::shared_ptr<serialhandler> serial_handler_ptr;
typedef boost::shared_ptr<SocketHandler> socket_handler_ptr;

class driveserver{

private:    
    serial_handler_ptr serialHandler;
    socket_handler_ptr socketHandler;        
public:
    driveserver();
    ~driveserver();        
    int parseAndSend(const char [] buf) const;
    int start();
   
};






#endif // drive_server_h