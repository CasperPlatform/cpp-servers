/**
* 
*/


#include <driveserver.hpp>
#include "sqlite3.h"

static sqlite3 *sqlite_open()
{
    sqlite3 *sqlite_conn;

    int error;
    if ((error = sqlite3_open("db/db.db", &sqlite_conn)) != 0)
    {
        printf("ohoh %d\n", error);
        return NULL;
    }

    return sqlite_conn;
}

int main(){
    
    
    sqlite3 *sqlite_conn;
    
    if ((sqlite_conn = sqlite_open()) == NULL)
    {   
        printf("sqlite3 failed... exiting");
        return -1;
    }
    else{
        printf("DB-open!\n");
    }
    
    printf("test\n");
/*
    std::string comPort = "/dev/cu.wchusbserial1420";

    serialhandler sh;


    if(!sh.start(comPort.c_str(), 9600))
    {
        return -1;
    }

    sh.write_string("Bajs\n");

    sleep(5);

    sh.stop();

    */
    driveserver drive;
    drive.start();
    //SocketHandler* socket = new SocketHandler();

    //socket->startServer("127.0.0.1", "6000");

    return 0;
}



////// SQLITE3 Snippets ///////
//     sqlite3 *sqlite_conn;
//     sqlite3_stmt *stmt;

//     list_type = (char *)cbdata;

//     req_info = mg_get_request_info(conn);



//     if (!strstr(req_info->request_method, "GET"))
//     {

//         return -1;
//     }

//     if ((sqlite_conn = sqlite_open()) == NULL)
//     {
//         return -1;
//     }

//     index = extract_uri_index(req_info, list_type);
//     if (index < 0)
//     {
//         return -1;
//     }
//     else if (index == INDEX_ALL)
//     {
//         asprintf(&query, "SELECT id,timestamp, zone, central,card,sub_card,type,muted, text1, text2 FROM %s", list_type);
//     }
//     else
//     {
//         asprintf(&query, "SELECT id,timestamp, zone, central,card,sub_card,type,muted, text1, text2 FROM %s WHERE id='%d'", list_type, index);
//     }

//     if (sqlite3_prepare_v2(sqlite_conn, query, strlen(query), &stmt, NULL) != SQLITE_OK)
//     {
//         free(query);
//         return -1;
//     }

//     free(query);

//     jarray = json_object_new_array();

//     while (sqlite3_step(stmt) == SQLITE_ROW)
//     {
//         json_object_array_add(jarray, sqlite_to_json(stmt));
//     }

//     sqlite3_finalize(stmt);

//     sqlite3_close(sqlite_conn);

//     if (json_object_array_length(jarray) == 0)
//     {
//         mg_printf(conn, "HTTP/1.1 204 OK\r\nContent-Type: application/json\r\n\r\n");
//     }
//     else
//     {
//         mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
//         mg_printf(conn, "%s", json_object_to_json_string(jarray));
//     }

//     return 1;