#include<iostream>
#include<string>
#include<cstring>
#include<memory>
#include"Log.hpp"

#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

using namespace LogModule;

class UDPServer{
public:
    UDPServer(uint16_t port ) : _is_running(false), _sockfd(-1)
    {
        memset(&_server_addr, 0, sizeof(_server_addr));
        //设置server端的ip和port
        _server_addr.sin_family = AF_INET;
        _server_addr.sin_addr.s_addr = INADDR_ANY;//其实是0，能接收所有ip。若绑定固定ip则只能接收一个ip的消息
        _server_addr.sin_port = htons(port);
    }
    ~UDPServer(){
    }
    void init(){
        // 建立一个UDP协议的网络socket
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(_sockfd < 0){
            LOG(LogLevel::FATAL)<<"socket error";
            exit(1);
        }

        //绑定sever端的ip和port
        int ret = bind(_sockfd, (struct sockaddr*)&_server_addr, sizeof(_server_addr));
        if(ret<0){
            LOG(LogLevel::ERROR)<<"bind error";
            exit(2);
        }
    }

    void start(){
        _is_running = true;
        char buffer[1024];
        while(_is_running){
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            //UDP协议，直接接收消息。中间的0表示阻塞等待
            ssize_t recv_len = recvfrom(_sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr *)&client_addr, &client_addr_len);
            if(recv_len > 0){
                buffer[recv_len] = '\0'; // 以'\0'结尾
                in_addr_t ip = client_addr.sin_addr.s_addr;
                char ip_str[16];
                inet_ntop(client_addr.sin_family, &ip, ip_str, sizeof(ip_str));
                uint16_t port = ntohs(client_addr.sin_port);
                LOG(LogLevel::INFO)<<"recv msg from "<<ip_str<<":"<<port;
            }
            std::string ret_msg = "server return:" + std::string(buffer);
            //将消息发送回去
            sendto(_sockfd, ret_msg.c_str(), ret_msg.size(), 0, (struct sockaddr *)&client_addr, client_addr_len);
        }
        _is_running = false;
    }



private:
    int _sockfd;
    struct sockaddr_in _server_addr;
    bool _is_running;
};


