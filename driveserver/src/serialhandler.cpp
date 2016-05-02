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
    
}

