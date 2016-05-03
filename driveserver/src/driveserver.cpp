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
    return 0;
}
int driveserver::start(){
    this->serialHandler = serial_handler_ptr(new serialhandler());
    this->socketHandler = socket_handler_ptr(new SocketHandler(this));
    //this->socketHandler->setServer(*this);
    this->socketHandler->startServer("127.0.0.1", "6000");
    return 0;
}