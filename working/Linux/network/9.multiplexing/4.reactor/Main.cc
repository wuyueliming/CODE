#include <iostream>
#include <string>
#include "Reactor.hpp"
#include "Listener.hpp"
#include "Channel.hpp"
#include "Log.hpp"
#include "Common.hpp"
#include "Protocol.hpp"
#include "NetCal.hpp"

static void Usage(std::string proc)
{
    std::cerr << "Usage: " << proc << " port" << std::endl;
}

//./server port
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(USAGE_ERR);
    }

    LogModule::ConsoleLogStrategy();
    uint16_t port = std::stoi(argv[1]);
    // 构建一个业务模块
    std::shared_ptr<Cal> cal = std::make_shared<Cal>();

    // 构建协议对象
    std::shared_ptr<Protocol> protocol = std::make_shared<Protocol>([&cal](Request &req) -> Response
                                                                    { return cal->Execute(req); });

    // 构建Listener对象
    std::shared_ptr<Connection> conn = std::make_shared<Listener>(port);
    conn->RegisterHandler([&protocol](std::string &inbuffer) -> std::string { // 这个匿名函数就是要被Channel
        LOG(LogLevel::DEBUG) << "进入到匿名函数中...";
        std::string response_str;
        while (true)
        {
            std::string package;
            if (!protocol->Decode(inbuffer, &package))
                break;
            // 我敢保证，我的packge一定是一个完整的请求，是字节流的
            response_str += protocol->Execute(package);
        }
        LOG(LogLevel::DEBUG) << "结束匿名函数中...: " << response_str;
        return response_str;
    });

    // 构建一个reactor模块
    std::unique_ptr<Reactor> R = std::make_unique<Reactor>();
    R->AddConnection(conn);

    R->Loop();

    return 0;
}