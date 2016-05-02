#include "serialhandler.h"


serialhandler::serialhandler(void) : set_eol_char('\n')
{
    
}
serialhandler::~serialhandler(void)
{
    stop();
}
char serialhandler::get_eol_char() const
{
    return this->end_of_line_char_;    
}
void serialhandler::set_eol_char(const char & c){
    this->end_of_line_char_ = c;
}
bool serialhandler::start(const char * com_port_name, int baud_rate){
    boost::system::error_code ec;

    if(port)
    {
        std::cout << "Port allready open." << std::endl;

        return false;
    }

    port = serial_port_ptr(new boost::asio::serial_port(io_service));

    port->open(com_port_name, ec);

    if(ec)
    {
        std::cout << "Open Failed. com port name = " << com_port_name << ", e= " << ec.message().c_str() << std::endl;

        return false;
    }

    port->set_option(boost::asio::serail_port_base::baud_rate(baud_rate));

    boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

    async_read();

    return true;
}

void serialhandler::stop()
{
    boost::mutex::scoped_lock look(mutex);

    if(port)
    {
        port->cancel();
        port->close();
        port->reset();
    }

    io_service.stop();
    io_service.reset();
}

int serialhandler::write(const std::string &buf)
{
    return write_bytes(buf.c_str, buf.size());
}

int serialhandler::write_bytes(const char *buf, const int &size)
{
    boost::system::error_code ec;

    if(!port) return -1;
    if(size==0) return 0;

    return port->write_some(boost::asio::buffer(buf, size), ec);
}

void