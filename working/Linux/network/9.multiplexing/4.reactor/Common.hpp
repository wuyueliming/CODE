#pragma once

#include <iostream>
#include <functional>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>


enum ExitCode
{
    OK = 0,
    USAGE_ERR,
    SOCKET_ERR,
    BIND_ERR,
    LISTEN_ERR,
    CONNECT_ERR,
    FORK_ERR,
    OPEN_ERR,
    EPOLL_CREATE_ERR,
    EPOLL_CTL_ERR
};

class NoCopy
{
public:
    NoCopy(){}
    ~NoCopy(){}
    NoCopy(const NoCopy &) = delete;
    const NoCopy &operator = (const NoCopy&) = delete;
};

int defaultport = 8080;

void SetNonBlock(int fd)
{
    int fl = fcntl(fd, F_GETFL);
    if(fl < 0)
    {
        return;
    }
    fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}

#define CONV(addr) ((struct sockaddr*)&addr)