/**
*	Casper drive_server Header 
*	Author @Pontus Pohl and @Linus Eiderström Swahn
*/

#ifndef lidarserver_hpp
#define lidarserver_hpp
class SocketHandler;
class serialhandler;
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
// #include <SocketHandler.hpp>
// #include <serialhandler.hpp>


/**
* **** OUTGOING ****
*/
// HEADER FLAGS
#define HEADER_START 0x48
#define HEADER_WALL_FLAG 0x77
#define HEADER_OBSTACLE_FLAG 0x6f
#define HEADER_CAR_CLAG 0x63
// SUBPACKET FLAGS
#define WALL_START_FLAG 0x4c
#define OBSTACLE_START_FLAG 0x49
#define CAR_START_FLAG 
// END FLAGS
#define CARRIAGE_RETURN 0x0d
#define LINE_FEED 0x0a
#define END_OF_TRANSMISSION 0x04
/**
* **** INCOMMING ****
*/
#define MAP_REQUEST_START_FLAG 0x53
// OTHER
#define READ_BUF 24





typedef boost::shared_ptr<SocketHandler> socket_handler_ptr;
typedef boost::shared_ptr<serialhandler> serial_handler_ptr;

class lidarserver{

private:    
    serial_handler_ptr serialHandler;
    socket_handler_ptr socketHandler;     
    std::array<char,READ_BUF> read_buf;
    std::string token; 
    char lidarStart[2];
    char lidarStop[2];
    static sqlite3 *sqlite_open();  
public:
    lidarserver();
    ~lidarserver();    
    int getMapMsg();    
    int parseRequest(std::array<char,20> buf, int len);
    int start();
    int verifyToken(const char token[]) const;
    
};









#endif // drive_server_hpp