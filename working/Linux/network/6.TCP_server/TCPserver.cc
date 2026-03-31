#include"TCPserver.hpp"



std::string defaultFunc(const std::string& msg,const InetAddr& clientAddr){
    std::string response;
    response = clientAddr.IP() + ":" + std::to_string(clientAddr.Port()) + " say: " + msg;
    return response;
}


// ./tcpserver 8080
int main(int argc,char* args[]){
    if(argc!=2){
        std::cerr<<"Usage: "<<args[0]<<" <port>"<<std::endl;
        return USAGE_ERR;
    }

    

    uint16_t port = std::stoi(args[1]);
    TCPserver server(port,[](const std::string& msg,const InetAddr& clientAddr){
        return defaultFunc(msg, clientAddr);
    });


    server.Init();
    server.start();


    return 0;
}




