//
// Created by Linus Eiderström Swahn on 01/05/16.
//

#ifndef SOCKETTEST_SOCKETTEST_H
#define SOCKETTEST_SOCKETTEST_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

class SocketTest {
private:
    struct addrinfo hints, *result, *p;
    int status;
    char ipString[INET6_ADDRSTRLEN];  // will point to the results
    void getAddress(char* address, char* port);

public:
    SocketTest();
    ~SocketTest();


    void startServer(char *address, char *port);
    void listenForMessages();
    void showAddress(char* address);
};


#endif //SOCKETTEST_SOCKETTEST_H
