#pragma once
#include"common.h"


class InetAddr{
public:
    InetAddr(){
        memset(&_addr, 0, sizeof(_addr));
    }
    InetAddr(const struct sockaddr_in& addr){//网络到主机
        _addr = addr;
        char str[16];
        inet_ntop(AF_INET, &addr.sin_addr, str, sizeof(str));
        _ip = str;
        _port = ntohs(addr.sin_port);
    }

    InetAddr(const std::string& ip,uint16_t port)://主机到网络
    _ip(ip),
    _port(port)
    {
        _addr.sin_family=AF_INET;
        _addr.sin_port=htons(_port);
        inet_pton(AF_INET, _ip.c_str(), &_addr.sin_addr.s_addr);
    }

    std::string IP() const{
        return _ip;
    }

    uint16_t Port() const{
        return _port;
    }

    struct sockaddr_in& Addr(){
        return _addr;
    }
    socklen_t AddrLen(){
        return (socklen_t)sizeof(_addr);
    }

    in_addr_t NetIp(){
        return _addr.sin_addr.s_addr;
    }

    uint16_t NetPort(){
        return _addr.sin_port;
    }

    std::string StringAddr(){
        return IP()+":"+std::to_string(Port());
    }

private:
    struct sockaddr_in _addr;
    std::string _ip;
    uint16_t _port;
};


