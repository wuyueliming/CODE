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

int main(int argc ,char* argv[]){
    if(argc != 3){
        LOG(LogLevel::ERROR)<<"Usage: "<<argv[0]<<" ip port";
        return 1;
    }
    std::string ip_str = argv[1];

    //创建socket
    int _sockfd = socket(AF_INET,SOCK_DGRAM,0);

    //设置远端地址
    sockaddr_in sever;
    memset(&sever,0,sizeof(sever));
    sever.sin_family = AF_INET;
    inet_pton(AF_INET, ip_str.c_str(), &sever.sin_addr);
    sever.sin_port = htons(atoi(argv[2]));

    //不要显示bind，首次发送消息时系统会自动获取ip并随即绑定一个port，如果固定port会影响其它进程
    //bind(_sockfd,(struct sockaddr*)&client, sizeof(client));


    char buffer[1024];
    while(true){
        std::string msg;
        std::getline(std::cin, msg);

        sendto(_sockfd, msg.c_str(), msg.size(), 0, (struct sockaddr *)&sever, sizeof(sever));

        
        socklen_t len = sizeof(sever);
        ssize_t n = recvfrom(_sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr *)&sever, &len);
        if(n > 0){
            buffer[n] = '\0';
            std::cout<<"recv: "<<buffer<<std::endl;
        }

    }




    return 0;
}
