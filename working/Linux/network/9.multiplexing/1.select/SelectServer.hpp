#pragma once

#include <iostream>
#include <memory>
#include <unistd.h>
#include "Socket.hpp"
#include "Log.hpp"

using namespace SocketModule;
using namespace LogModule;

class SelectServer
{
    const static int size = sizeof(fd_set) * 8;
    const static int defaultfd = -1;

public:
    SelectServer(int port) : _listensock(std::make_unique<TcpSocket>()), _isrunning(false)
    {
        _listensock->BuildTcpSocketMethod(port);
        for (int i = 0; i < size; i++)
            _fd_array[i] = defaultfd;

        _fd_array[0] = _listensock->Fd();
    }
    void Start()
    {
        _isrunning = true;
        while (_isrunning)
        {
            // 因为: listensockfd,也是一个fd，进程怎么知道listenfd上面有新连接到来了呢？
            // auto res = _listensock->Accept(); // 我们在select这里，可以进行accept吗？
            // 将listensockfd添加到select内部，让OS帮我关心listensockfd上面的读事件
            fd_set rfds;    // 定义fds集合
            FD_ZERO(&rfds); // 清空fds
            int maxfd = defaultfd;
            for (int i = 0; i < size; i++)
            {
                if (_fd_array[i] == defaultfd)
                    continue;
                // 1. 每次select之前，都要对rfds进行重置！
                FD_SET(_fd_array[i], &rfds);
                // 2. 最大fd，一定是变化的
                if (maxfd < _fd_array[i])
                {
                    maxfd = _fd_array[i]; // 更新出最大fd
                }
            }
            PrintFd();
            // struct timeval timeout = {0, 0};
            // select 返回之后，你怎么还知道哪些fd需要被添加到rfds，让select关心呢？
            // 所以：select要进行完整的设计，需要借助一个辅助数组！保存服务器历史获取过的所有的fd

            // rfds: 1111 1111
            // select负责事件就绪检测
            int n = select(maxfd + 1, &rfds, nullptr, nullptr, nullptr);
            // rfds: 0000 0000
            switch (n)
            {
            case -1:
                LOG(LogLevel::ERROR) << "select error";
                break;
            case 0:
                LOG(LogLevel::INFO) << "time out...";
                break;
            default:
                // 有事件就绪,就不仅仅是新连接到来了吧？读事件就绪啊？
                LOG(LogLevel::DEBUG) << "有事件就绪了..., n : " << n;
                Dispatcher(rfds); // 处理就绪的事件啊！
                break;
            }
        }

        _isrunning = false;
    }
    // 事件派发器
    void Dispatcher(fd_set &rfds /*, fd_set &wfds*/)
    {
        // 就不仅仅是新连接到来了吧？读事件就绪啊？ // 指定的文件描述符，在rfds里面，就证明该fd就绪了

        for (int i = 0; i < size; i++)
        {
            if (_fd_array[i] == defaultfd)
                continue;
            // fd合法，不一定就绪
            if (FD_ISSET(_fd_array[i], &rfds))
            {
                // fd_array[i] 上面一定是读就绪了
                // listensockfd 新连接到来，也是读事件就绪啊
                // sockfd 数据到来，读事件就绪啊
                if (_fd_array[i] == _listensock->Fd())
                {
                    // listensockfd 新连接到来
                    Accepter();
                }
                else
                {
                    // 普通的读事件就绪
                    Recver(_fd_array[i], i);
                }
            }

            // if (FD_ISSET(fd_array[i], &wfds))
            // {
            //     // fd_array[i] 上面一定是读就绪了
            // }
        }
    }

    // 链接管理器
    void Accepter()
    {
        InetAddr client;
        int sockfd = _listensock->Accept(&client); // accept会不会阻塞?
        if (sockfd >= 0)
        {
            // 获取新链接到来成功, 然后呢？？能不能直接
            // read/recv()， sockfd是否读就绪，我们不清楚
            // 只有谁最清楚，未来sockfd上是否有事件就绪？select！
            // 将新的sockfd，托管给select！
            // 如何托管? 将新的fd放入辅助数组！
            LOG(LogLevel::INFO) << "get a new link, sockfd: "
                                << sockfd << ", client is: " << client.StringAddr();
            int pos = 0;
            for (; pos < size; pos++)
            {
                if (_fd_array[pos] == defaultfd)
                    break;
            }
            if (pos == size)
            {
                LOG(LogLevel::WARNING) << "select server full";
                close(sockfd);
            }
            else
            {
                _fd_array[pos] = sockfd;
            }
        }
    }

    // IO处理器
    void Recver(int fd, int pos)
    {
        char buffer[1024];
        // 我在这里读取的时候，会不会阻塞?
        ssize_t n = recv(fd, buffer, sizeof(buffer)-1, 0); // recv写的时候有bug吗？
        if(n > 0)
        {
            buffer[n] = 0;
            std::cout << "client say@ "<< buffer << std::endl;
        }
        else if(n == 0)
        {
            LOG(LogLevel::INFO) << "clien quit...";
            // 1. 不要让select在关系这个fd了
            _fd_array[pos] = defaultfd;

            // 2. 关闭fd
            close(fd);
        }
        else 
        {
            LOG(LogLevel::ERROR) << "recv error";
            // 1. 不要让select在关系这个fd了
            _fd_array[pos] = defaultfd;

            // 2. 关闭fd
            close(fd);
        }
    }
    void PrintFd()
    {
        std::cout << "_fd_array[]: ";
        for (int i = 0; i < size; i++)
        {
            if (_fd_array[i] == defaultfd)
                continue;
            std::cout << _fd_array[i] << " ";
        }
        std::cout << "\r\n";
    }
    void Stop()
    {
        _isrunning = false;
    }
    ~SelectServer()
    {
    }

private:
    std::unique_ptr<Socket> _listensock;
    bool _isrunning;

    int _fd_array[size];
};