#include <videoserver.hpp>
#include <sockethandler.hpp>
#include <camerahandler.hpp>

videoserver::videoserver() : service_thread(std::bind(&videoserver::mainLoop, this))
{
    std::cout << "Starting videoserver" << std::endl;
    
    this->camera_handler = camera_handler_ptr(new camerahandler()); 
    this->socket_handler = socket_handler_ptr(new sockethandler(this, 6000));
    
    gettimeofday(&startTime, NULL);
    videoActive = false;
}

void videoserver::mainLoop()
{
    while(true)
    {
        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);

        if(currentTime.tv_sec > startTime.tv_sec)
        {
            videoActive = false;
            gettimeofday(&startTime, NULL);
        }
        
        if(videoActive)
        {
            socket_handler->sendFrame(camera_handler->grabFrame());
        }
    }
}

void videoserver::parseMessage(char* message, int len)
{
    if(message[0] != 0x01)
    {
        std::cout << "Wrong message header." << std::endl;
        return;
    }
    // extract token.
    char tmp[17];
    for(int i = 1; i < 17; i++){
        tmp[i-1] = message[i];    
    }
    tmp[16] = '\0';
    printf("token is %s\n",tmp);
    // Do sqlite stuff if needed
    if(token == "")
    {
        if(verifyToken(tmp) == -1)
        {
            printf("token verification failed\n");
            return;
        } 
        token = std::string(tmp);   
    }

    char flag = message[17];

    if(flag == 'S')
    {
        gettimeofday(&startTime, NULL);
        videoActive = true;

        std::cout << "Start Sending Video." << std::endl;
    }
    if(flag == 's')
    {
        videoActive = false
        gettimeofday(&startTime, NULL);

        std::cout << "Stop Sending Video." << std::endl;
    }
    if(flag == 'I')
    {
        gettimeofday(&startTime, NULL);

        std::cout << "Recieved Idle Update." << std::endl;
    }
}

int videoserver::verifyToken(const char token[]) const{
    
    sqlite3 *sqlite_conn;
    sqlite3_stmt *stmt;
    char *query;
    
    if ((sqlite_conn = sqlite_open()) == NULL)
    {
        printf("Failed to open db\n");
        return -1;
    }
    
    time_t rawtime;
    time(&rawtime);
    struct tm *currentTime;
    currentTime = localtime ( &rawtime );
    const int TIME_STRING_LENGTH = 20;
    char buffer [TIME_STRING_LENGTH];
    
    strftime(buffer, TIME_STRING_LENGTH, "%Y-%m-%d %H:%M:%S", currentTime);

    asprintf(&query, 
            "select userId from tokens where token=\"%s\" and expiration>\"%s\""
            ,token
            ,buffer);
    
    printf("query is : %s\n", query);
    //printf("%s\n",buffer);
  
    if (sqlite3_prepare_v2(sqlite_conn, query, strlen(query), &stmt, NULL) != SQLITE_OK)
    {
        free(query);
        return -1;
    }   
   
    int uid;
    int c = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        c++;
        printf("got something back\n");
        uid = sqlite3_column_int(stmt,0);
        printf("uid is: %d\n", uid);
    }
    if(c == 0){
        printf("no token found\n");
        free(query);
        sqlite3_finalize(stmt);
        sqlite3_close(sqlite_conn);
        //free(currentTime);
        return -1;
    }
    else
    {
        //free(currentTime);
        
        time(&rawtime);
        currentTime = localtime ( &rawtime );
        
        for(int i = 0; i < 25; i++){
            if(currentTime->tm_min == 59){
                currentTime->tm_min = 0;
                currentTime->tm_hour += 1;
                continue;
            }
            currentTime->tm_min++;
        }
        strftime(buffer, TIME_STRING_LENGTH, "%Y-%m-%d %H:%M:%S", currentTime);
        
        asprintf(&query,"");
     
        asprintf(&query,
                "update tokens set expiration=\"%s\" where userId=%d",
                buffer,
                uid);
        printf("query2 is : %s\n", query);
        
        if (sqlite3_prepare_v2(sqlite_conn, query, strlen(query), &stmt, NULL) != SQLITE_OK)
        {
            free(query);
            sqlite3_finalize(stmt);
            sqlite3_close(sqlite_conn);
            return -1;
        }
        free(query);
        // sqlite3_bind_text(stmt,1,buffer,-1,SQLITE_TRANSIENT);
        // sqlite3_bind_int(stmt,2,uid);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        sqlite3_close(sqlite_conn);
        
    }
    
    // free(token);
    // free(tm);
    
    
    printf("statement ok\n");
    return 1;
}

sqlite3 * videoserver::sqlite_open()
{
    sqlite3 *sqlite_conn;

    int error;
    if ((error = sqlite3_open("/home/pi/db.db", &sqlite_conn)) != 0)
    {
        printf("ohoh %d\n", error);
        return NULL;
    }
    return sqlite_conn;
}

videoserver::~videoserver()
{
    service_thread.join();
}