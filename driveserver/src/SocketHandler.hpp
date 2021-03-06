/**
*	Casper SocketHandler Header 
*	Author @Pontus Pohl and @Linus Eiderström Swahn
*/

#ifndef SOCKETHANDLER_SOCKETHANDLER_H
#define SOCKETHANDLER_SOCKETHANDLER_H



class driveserver;
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
//#include <driveserver.hpp>


typedef boost::shared_ptr<driveserver> drive_server_ptr;

class SocketHandler {
private:
    drive_server_ptr driveServer;
    struct addrinfo hints, *result, *p;
    int status;
    char ipString[INET6_ADDRSTRLEN];  // will point to the results
    void getAddress(char* address, char* port);
    void *get_in_addr(struct sockaddr *sa);
public:
    SocketHandler();
    ~SocketHandler();
    SocketHandler(driveserver * server);
    //int setServer(driveserver & server) const;
    


    void startServer(char *address, char *port);
    void listenForMessages();
    void showAddress(char* address);
};


#endif //SOCKETHANDLER_SOCKETHANDLER_H
