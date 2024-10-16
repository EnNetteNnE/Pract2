
#include "../code.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <thread>
#include <future>

#define DEFAULT_PORT 1613
#define ERROR_S "SERVER ERROR: "
#define BUFFER_SIZE 1024 
#define CLIENT_CLOSE_CONNECTION_SYMBOL '#'

bool is_client_connection_close(const char* msg);


int main(int argc, char const* argv[]) {



    string fileName = "../schems.json";
    string schemaName = "";
    int tuplesLimit = 0;
    MyHash<string, MyArr<string>*>* jsonStructure = HCREATE<string, MyArr<string>*>(10);
    MyArr<string>* keys = MCREATE<string>(10);

    ReadJsonFile(fileName, schemaName, tuplesLimit, *jsonStructure, *keys);

    MyHash<string, int>* numb = HCREATE<string, int>(10);
    for (int i = 0; i < keys->len; i++) {
        HSET<string, int>(*numb, keys->data[i], 1);
    }



    int client;
    int server;

    struct sockaddr_in server_address;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        std::cout << ERROR_S << "establishing socket error.";
        exit(0);
    }

    std::cout << "SERVER: Socked for server was successfuly created\n";

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    // соеденяем сокет с инфой о сети, где он будет запущен
    int ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address));

    if (ret < 0) {
        std::cout << ERROR_S << "binding connection.";
        return -1;
    }

    socklen_t size = sizeof(server_address);
    std::cout << "SERVER: " << "Listening clients...\n";
    listen (client, 1); // сервер начинает слушать порт, передаем соккет

    // если к ip по нашему порту было обращение с другого сокета, то они связываются
    server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
    if(server < 0) {
        std::cout << ERROR_S << "Can't acceptingclient.\n"; 
    }


    char buffer[BUFFER_SIZE];
    bool isExit = false;
    while(server > 0) {
        strcpy(buffer, "=> Server conected!\n");
        send(server, buffer, BUFFER_SIZE, 0);
        std::cout << "=> Connected to the client #1" << std::endl << "Enter # to end the connection\n\n";

        std::cout << "Clients request: ";
        recv(server, buffer, BUFFER_SIZE, 0);
        std::cout << buffer << std::endl;

        if(is_client_connection_close(buffer)) {
            isExit = true;
        }

        while(!isExit) {

            string sql;
            for (char i : buffer) {
                if (i == 0) {
                    break;
                }
                sql.push_back(i);
            }
            
            string str;

            //std::thread thr(code, std::ref(str), sql, *jsonStructure, *numb, schemaName, tuplesLimit, *keys);
            //thr.join();


            auto fut = async(code, std::ref(str), std::ref(sql), std::ref(*jsonStructure), std::ref(*numb), std::ref(schemaName), std::ref(tuplesLimit), std::ref(*keys));

            int result = fut.get();
         
            //code(str, sql, *jsonStructure, *numb, schemaName, tuplesLimit, *keys);


            for(int i = 0; i < str.size(); i++) {
                buffer[i] = str[i];
            }

            for(int i = str.size(); i < BUFFER_SIZE; i++) {
                buffer[i] = 0;
            }




            send(server, buffer, BUFFER_SIZE, 0);
            std::cout << "A response has been sent to the client\n";

            std::cout << "Clients request: ";
            recv(server, buffer, BUFFER_SIZE, 0);
            std::cout << buffer << std::endl;
            if(is_client_connection_close(buffer)) {
                break;
            }
        }

        std::cout << "\n GoodBye..." << std::endl;
        isExit = false;
        exit(1);
    }

    return 0;
}


bool is_client_connection_close(const char* msg) {
    for(int i = 0; i < strlen(msg); ++i) {
        if(msg[i] == CLIENT_CLOSE_CONNECTION_SYMBOL) {
            return true;
        }
    }
    return false;
}