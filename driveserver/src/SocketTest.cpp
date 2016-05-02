//
// Created by Linus Eiderström Swahn on 01/05/16.
//


#include <arpa/inet.h>
#include "SocketTest.h"

SocketTest::SocketTest()
{

}

void SocketTest::startListen(char *address, char *port)
{
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int socketDescriptor, newSocketDescriptor;

    getAddress(address, port);

    socketDescriptor = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    int bindResult = bind(socketDescriptor, result->ai_addr, result->ai_addrlen);

    if(bindResult == -1)
    {
        printf("error");
    }
    else if(bindResult == 0)
    {
        printf("Now listening on: %s", result->ai_addr);
    }

    listen(socketDescriptor, 5);


    addr_size = sizeof their_addr;
    newSocketDescriptor = accept(socketDescriptor, (struct sockaddr *)&their_addr, &addr_size);

    printf("A conneciton was made");


}

void SocketTest::getAddress(char *address, char *port)
{
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if ((status = getaddrinfo(address, port, &hints, &result)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
}

void SocketTest::showAddress(char *address)
{
    getAddress(address, NULL);

    printf("IP addresses for %s:\n\n", address);

    for(p = result; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipVersion;

        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) // IPv4
        {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipVersion = "IPv4";
        }
        else // IPv6
        {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipVersion = "IPv6";
        }

        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipString, sizeof ipString);
        printf("  %s: %s\n", ipVersion, ipString);
    }

    freeaddrinfo(result); // free the linked list
}
