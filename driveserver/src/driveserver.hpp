/**
*	Casper drive_server Header 
*	Author @Pontus Pohl and @Linus Eiderström Swahn
*/

#ifndef driveserver_hpp
#define driveserver_hpp
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <sqlite3.h>
#include <SocketHandler.hpp>
#include <serialhandler.hpp>

// flag defs
#define DRIVE_FLAG 0x44
#define BACKWARD_FLAG 0x42
#define FORWARD_FLAG 0x46
#define RIGHT_ANGLE_FLAG 0x52
#define LEFT_ANGLE_FLAG 0x4c
#define IDLE_DRIVE_FLAG 0x49


typedef boost::shared_ptr<SocketHandler> socket_handler_ptr;
typedef boost::shared_ptr<serialhandler> serial_handler_ptr;

class driveserver{

private:    
    serial_handler_ptr serialHandler;
    socket_handler_ptr socketHandler;        
public:
    driveserver();
    ~driveserver();        
    int parseAndSend(const char buf[]) const;
    int start();
};









#endif // drive_server_hpp