/**
*	Casper drive_server Implementation 
*	Author @Pontus Pohl and @Linus Eiderström Swahn
*/
#include <driveserver.hpp>

driveserver::driveserver(){
    
}
driveserver::~driveserver(){}

int driveserver::parseAndSend(const char buf[]) const{
    printf("got a buffer to send to arduino\n %s",buf);
}
int driveserver::start(){
    this->serialHandler = new serial_handler_ptr(new serialhandler());
    this->socketHandler = new socket_handler_ptr(new SocketHandler(this));
}