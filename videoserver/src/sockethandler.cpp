#include <sockethandler.hpp>

sockethandler::sockethandler(unsigned short local_port) : 
socket(io_service, udp::endpoint(udp::v4(), local_port))
{
    printf("Server starting on: %i\n", local_port);  
    start_receive();
    io_service.run();
}

sockethandler::~sockethandler()
{
    io_service.stop();
}

void sockethandler::start_receive()
{
    socket.async_receive_from(
        boost::asio::buffer(recv_buffer), remote_endpoint,
        boost::bind
        (
            &sockethandler::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void sockethandler::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    std::string message_string(recv_buffer.data(), recv_buffer.data() + bytes_transferred);

   std::cout << "message \"" << message_string.c_str() << "\" received." << std::endl;
    
    if (!error || error == boost::asio::error::message_size)
    {
        boost::shared_ptr<std::string> message(new std::string(message_string.c_str()));

        socket.async_send_to(boost::asio::buffer(*message), remote_endpoint,
            boost::bind(&sockethandler::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

        start_receive();
    }
}

void sockethandler::handle_send(boost::shared_ptr<std::string> message,
    const boost::system::error_code& error,
    std::size_t bytes_transferred)
{
    std::cout << "Sent message \"" << message->c_str() << "\"" << std::endl;
}
