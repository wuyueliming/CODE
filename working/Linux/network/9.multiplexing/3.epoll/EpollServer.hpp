#pragma once

#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/epoll.h>
#include "Socket.hpp"
#include "Log.hpp"

using namespace SocketModule;
using namespace LogModule;

// 暂时不做过多解耦
class EpollServer
{
    const static int size = 64;
    const static int defaultfd = -1;

public:
    EpollServer(int port) : _listensock(std::make_unique<TcpSocket>()), _isrunning(false), _epfd(defaultfd)
    {
        // 1. 创建listensocket
        _listensock->BuildTcpSocketMethod(port); // 3
        // 2. 创建epoll模型
        _epfd = epoll_create(256);
        if (_epfd < 0)
        {
            LOG(LogLevel::FATAL) << "epoll_create error";
            exit(EPOLL_CREATE_ERR);
        }
        LOG(LogLevel::INFO) << "epoll_create success: " << _epfd; // 4

        // 3. 将listensocket设置到内核中！
        struct epoll_event ev; // 有没有设置到内核中，有没有rb_tree中新增节点？？没有！！
        ev.events = EPOLLIN;
        ev.data.fd = _listensock->Fd(); // TODO : 这里未来是维护的是用户的数据，常见的是fd
        // ev.data.ptr = _listensock.get();

        int n = epoll_ctl(_epfd, EPOLL_CTL_ADD, _listensock->Fd(), &ev);
        if (n < 0)
        {
            LOG(LogLevel::FATAL) << "add listensockfd failed";
            exit(EPOLL_CTL_ERR);
        }
    }
    void Start()
    {
        int timeout = -1;
        _isrunning = true;
        while (_isrunning)
        {
            // 能不能直接accept呢？？不能！应该干什么？
            int n = epoll_wait(_epfd, _revs, size, timeout);
            switch (n)
            {
            case 0:
                LOG(LogLevel::DEBUG) << "timeout...";
                break;
            case -1:
                LOG(LogLevel::ERROR) << "epoll error";
                break;
            default:
                Dispatcher(n);
                break;
            }
        }

        _isrunning = false;
    }
    // 事件派发器
    void Dispatcher(int rnum)
    {
        LOG(LogLevel::DEBUG) << "event ready ..."; // LT: 水平触发模式--epoll默认
        for (int i = 0; i < rnum; i++)
        {
            // epoll也要循环处理就绪事件--这是应该的，本来就有可能有多个fd就绪！
            int sockfd = _revs[i].data.fd;
            uint32_t revent = _revs[i].events;
            if (revent & EPOLLIN)
            { // 读事件就绪
                // listensockfd ready? normal socfd ready？？
                if (sockfd == _listensock->Fd())
                {
                    // 读事件就绪 && 新连接到来
                    Accepter();
                }
                else
                {
                    // 读事件就绪 && 普通socket可读
                    Recver(sockfd);
                }
            }
            // if(_revs[i].events & EPOLLOUT)
            // {// 写事件就绪

            // }
        }
    }

    // 链接管理器
    void Accepter()
    {
        InetAddr client;
        // 新连接到来 --- 至少有一个连接到来 --- accept一次 --- 绝对不会阻塞
        int sockfd = _listensock->Accept(&client); // accept会不会阻塞? 0 or 1
        if (sockfd >= 0)
        {
            // 获取新链接到来成功, 然后呢？？能不能直接
            // read/recv()， sockfd是否读就绪，我们不清楚
            // 只有谁最清楚，未来sockfd上是否有事件就绪？select！
            // 将新的sockfd，托管给select！
            // 如何托管? 将新的fd放入辅助数组！
            LOG(LogLevel::INFO) << "get a new link, sockfd: "
                                << sockfd << ", client is: " << client.StringAddr();
            // 能不能直接recv??? 不能！！！
            // 将新的sockfd添加到内核！
            struct epoll_event ev;
            ev.events = EPOLLIN;
            ev.data.fd = sockfd;
            int n = epoll_ctl(_epfd, EPOLL_CTL_ADD, sockfd, &ev);
            if (n < 0)
            {
                LOG(LogLevel::WARNING) << "add listensockfd failed";
            }
            else
            {
                LOG(LogLevel::INFO) << "epoll_ctl add sockfd success: " << sockfd;
            }
        }
    }

    // IO处理器
    void Recver(int sockfd)
    {
        char buffer[1024];
        // 我在这里读取的时候，会不会阻塞? 本次读取，不会被阻塞
        ssize_t n = recv(sockfd, buffer, sizeof(buffer) - 1, 0); // recv写的时候有bug吗？
        if (n > 0)
        {
            buffer[n] = 0;
            std::cout << "client say@ " << buffer << std::endl;
        }
        else if (n == 0)
        {
            LOG(LogLevel::INFO) << "clien quit...";
            // 2. 从epoll中移除fd的关心 && 关闭fd -- 细节：epoll_ctl: 只能移除合法fd -- 先移除，在关闭！！
            int m = epoll_ctl(_epfd, EPOLL_CTL_DEL, sockfd, nullptr);
            if(m > 0)
            {
                LOG(LogLevel::INFO) << "epoll_ctl remove sockfd success: " << sockfd;
            }
            close(sockfd);
        }
        else
        {
            LOG(LogLevel::ERROR) << "recv error";
            // 2. 关闭fd
            int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, sockfd, nullptr);
            if(ret > 0)
            {
                LOG(LogLevel::INFO) << "epoll_ctl remove sockfd success: " << sockfd;
            }
            close(sockfd);
        }
    }
    void Stop()
    {
        _isrunning = false;
    }
    ~EpollServer()
    {
        _listensock->Close();
        if (_epfd > 0)
            close(_epfd);
    }

private:
    std::unique_ptr<Socket> _listensock;
    bool _isrunning;
    int _epfd;

    struct epoll_event _revs[size];
};