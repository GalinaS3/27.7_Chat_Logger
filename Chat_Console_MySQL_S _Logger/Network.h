#pragma once
#include<string>
#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<memory.h>
#include"Logger.h"
#include"CurrentTime.h"
#include<thread>

class Network
{
public:
    Network();
    ~Network();
    int connectServerOpen();
    int connectClientOpen();
    void sendMessage(int connection, const std::string &str);
    std:: string reseiveMessage(int connection);
    void connectClose(int socket_discriptor);
};