#ifndef video_server_hpp
#define video_server_hpp

class camerahandler;
class sockethandler;
#include <sqlite3.h>
#include <string>
#include <stdio.h>
#include <boost/thread.hpp>
#include <sys/time.h>

typedef boost::shared_ptr<sockethandler> socket_handler_ptr;
typedef boost::shared_ptr<camerahandler> camera_handler_ptr;

class videoserver
{
    private:
        camera_handler_ptr camera_handler;
        socket_handler_ptr socket_handler;
        std::string token; 
        struct timeval startTime;
        bool videoActive;
        boost::thread service_thread;

        static sqlite3 *sqlite_open(); 
        int verifyToken(const char token[]) const; 
        void mainLoop();
    public: 
        videoserver();
        ~videoserver();
        void parseMessage(char* message, int len);
        void startServer();
        void startVideo();
        void stopServer();
        void stopVideo();
};

#endif //video_server_hpp