//
// Created by Linus Eiderström Swahn on 01/05/16.
//


#include <arpa/inet.h>
#include "SocketTest.h"

SocketTest::SocketTest()
{

}

void SocketTest::startServer(char *address, char *port)
{
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int socketDescriptor, newSocketDescriptor;
    int numbytes;

    int MAXBUFLEN = 100;
    char buf[MAXBUFLEN];
    char s[INET6_ADDRSTRLEN];

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
        freeaddrinfo(result);
    }

    printf("listener: waiting to recvfrom...\n");

    while(1)
    {
        addr_size = sizeof their_addr;
        if ((numbytes = recvfrom(socketDescriptor, buf, MAXBUFLEN - 1, 0, (struct sockaddr *) &their_addr, &addr_size)) == -1) {
            perror("recvfrom");
            exit(1);
        }

        printf("listener: got packet from %s\n",
               inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof s));
        printf("listener: packet is %d bytes long\n", numbytes);
        buf[numbytes] = '\0';
        printf("listener: packet contains \"%s\"\n", buf);
    }
}

void listenForMessages()
{

}

void *SocketTest::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void SocketTest::getAddress(char *address, char *port)
{
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM; // UDP stream sockets
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
