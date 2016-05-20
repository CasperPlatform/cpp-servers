#ifndef socket_handler_hpp
#define socket_handler_hpp

class videoserver;
#include <iostream>
#include <stdio.h>
#include <string>
#include <array>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>
#include <tgmath.h>
#include <camerahandler.hpp>

typedef boost::shared_ptr<videoserver> video_server_ptr;

using boost::asio::ip::udp;

class sockethandler
{           
    public: 
        sockethandler(videoserver* server, unsigned short local_port);
        ~sockethandler();
        void sendFrame(camerahandler::frame imageFrame);

    private:
        boost::asio::io_service io_service;
        udp::socket socket;
        udp::endpoint remote_endpoint;
        boost::array<char, 8000> recv_buffer;
        boost::thread service_thread;
        video_server_ptr videoServer;
        unsigned int imageNumber;
        void initialize();
        void start_receive();
        void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
        void handle_send(   const boost::shared_ptr<std::string> message, 
                            const boost::system::error_code& error, 
                            std::size_t bytes_transferred);              
};

#endif // socket_handler_hpp
