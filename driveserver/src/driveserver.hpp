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
#include <array>
#include <sqlite3.h>
#include <time.h>
#include <SocketHandler.hpp>
#include <serialhandler.hpp>

// flag defs
#define DRIVE_FLAG 0x44
#define BACKWARD_FLAG 0x42
#define FORWARD_FLAG 0x46
#define RIGHT_ANGLE_FLAG 0x52
#define LEFT_ANGLE_FLAG 0x4c
#define IDLE_DRIVE_FLAG 0x49
#define CARRIAGE_RETURN 0x0d
#define LINE_FEED 0x0a
#define END_OF_TRANSMISSION 0x04
#define READ_BUF 24





typedef boost::shared_ptr<SocketHandler> socket_handler_ptr;
typedef boost::shared_ptr<serialhandler> serial_handler_ptr;

class driveserver{

private:    
    serial_handler_ptr serialHandler;
    socket_handler_ptr socketHandler;     
    std::array<char,READ_BUF> read_buf;
    std::string token; 
    static sqlite3 *sqlite_open();  
public:
    driveserver();
    ~driveserver();        
    int parseAndSend(char buf[], int len);
    int start();
    int verifyToken(const char token[]) const;
    
};









#endif // drive_server_hpp