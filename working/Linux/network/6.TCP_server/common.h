#pragma once
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

#include<iostream>
#include<string>
#include<cstring>
#include<unistd.h>
#include<sys/wait.h>


enum EXIT_CODE{
    FINE,
    USAGE_ERR,
    READ_ERR,
    SOCKET_ERR,
    BIND_ERR,
    LISTEN_ERR,
    ACCEPT_ERR,
    CONNECT_ERR,
    FORK_ERR,
};

