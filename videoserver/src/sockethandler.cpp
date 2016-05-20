#include <sockethandler.hpp>
#include <videoserver.hpp>

sockethandler::sockethandler(videoserver* server, unsigned short local_port) : 
socket(io_service, udp::endpoint(udp::v4(), local_port)),
service_thread(std::bind(&sockethandler::initialize, this))
{
    this->videoServer = video_server_ptr(server);
    imageNumber = 0;
    printf("Server starting on: %i\n", local_port);
}

void sockethandler::initialize()
{
    start_receive();
    io_service.run();
}

sockethandler::~sockethandler()
{
    io_service.stop();
    service_thread.join();
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

void sockethandler::sendFrame(const unsigned char* frame, const unsigned int imageSize)
{
    std::vector<unsigned char> imageFrame = frame;

    imageNumber++;
    unsigned int packetLen = 8000;
    unsigned char packets = imageSize/packetLen;

    unsigned char header[11];
    header[0] = 0x01;
    header[1] = 0x56;

    header[2] = (imageNumber>>24) & 0xff;
    header[3] = (imageNumber>>16) & 0xff;
    header[4] = (imageNumber>>8) & 0xff;
    header[5] = imageNumber & 0xff;

    header[6] = packets;
    
    header[7] = (imageSize>>24) & 0xff;
    header[8] = (imageSize>>16) & 0xff;
    header[9] = (imageSize>>8) & 0xff;
    header[10] = imageSize & 0xff;

    boost::shared_ptr<std::string> message(new std::string(header, header + 11));

    socket.async_send_to(boost::asio::buffer(*message), remote_endpoint,
        boost::bind(&sockethandler::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
    
    for(int i = 0; i<packets; i++)
    {
        unsigned int packetLength = 6;
        if(i == packets-1)
        {
            packetLength += imageSize - (i*packetLen);
        }
        else
        {
            packetLength += packetLen;
        }
        
        std::array<unsigned char, packetLength> packet;
        packet[0] = 0x02;

        packet[1] = (imageNumber>>24) & 0xff;
        packet[2] = (imageNumber>>16) & 0xff;
        packet[3] = (imageNumber>>8) & 0xff;
        packet[4] = imageNumber & 0xff;

        packet[5] = i;

        if(i == packets-1)
        {
            std::copy(imageFrame::begin() + i, imageFrame::begin() + i + (imageSize - i*8000), packet.begin() + 6);
        }
        else
        {
            std::copy(imageFrame::begin() + i, imageFrame::begin() + i + packetLen, packet.begin() + 6);
        }
        
        boost::shared_ptr<std::string> message(new std::string(packet, packet + packetLength));

        socket.async_send_to(boost::asio::buffer(*message), remote_endpoint,
            boost::bind(&sockethandler::handle_send, this, message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
    }
}

void sockethandler::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    std::string message_string(recv_buffer.data(), recv_buffer.data() + bytes_transferred);
    
    std::cout << "message \"" << message_string.c_str() << "\" received." << std::endl;
    
    if (!error || error == boost::asio::error::message_size)
    {
        
    }
    
    start_receive();
}

void sockethandler::handle_send(boost::shared_ptr<std::string> message,
    const boost::system::error_code& error,
    std::size_t bytes_transferred)
{
    std::cout << "Sent message \"" << message->c_str() << "\"" << std::endl;
}
