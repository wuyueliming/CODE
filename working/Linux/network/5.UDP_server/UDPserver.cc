#include"UDPserver.hpp"



int main(int argc, char* argv[])
{
    if(argc != 2){
        LOG(LogLevel::ERROR)<<"Usage: "<<argv[0]<<" port";
    }
    uint16_t port=std::stoi(argv[1]);
    UDPServer server(port);
    server.init();
    server.start();

    return 0;
}



