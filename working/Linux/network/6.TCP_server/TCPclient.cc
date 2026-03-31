#include "common.h"
#include "InetAddr.hpp"
#include "Log.hpp"

using namespace LogModule;

// ./tcpclient ip port
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        LOG(LogLevel::ERROR) << "usage error";
        exit(USAGE_ERR);
    }
    InetAddr server(argv[1], std::stoi(argv[2]));

    // 1.创建socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        LOG(LogLevel::ERROR) << "socket error";
        exit(SOCKET_ERR);
    }
    LOG(LogLevel::INFO) << "socket success";

    // 2.bind(无需显示绑定)

    // 3.请求连接
    int ret = connect(sockfd, (const sockaddr *)&server.Addr(), server.AddrLen());
    if (ret < 0)
    {
        LOG(LogLevel::ERROR) << "connect error";
        exit(CONNECT_ERR);
    }
    LOG(LogLevel::INFO) << "connect success";
    LOG(LogLevel::INFO) << "server: "<<server.StringAddr();


    char buffer[1024];
    while (true)
    {
        std::string msg;
        std::cout<<"please enter#";
        std::getline(std::cin, msg);
        // 4.给服务器发送消息
        write(sockfd, msg.c_str(), msg.size());
        // 5.获取结果
        int ret = read(sockfd, buffer, sizeof(buffer) - 1);
        if (ret > 0)
        {
            buffer[ret] = 0;
        }
        else if (ret < 0)
        {
            LOG(LogLevel::ERROR) << "read error";
            exit(READ_ERR);
        }else{
            LOG(LogLevel::INFO) << "server exit";
            exit(FINE);
        }
        std::cout << "server echo#"<<buffer;
    }

    return 0;
}
