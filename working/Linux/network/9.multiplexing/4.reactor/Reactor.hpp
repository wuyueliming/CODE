#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include "Epoller.hpp"
#include "Connection.hpp"
#include "Log.hpp"

using namespace LogModule;

// 反应堆
class Reactor
{
    static const int revs_num = 128;

private:
    bool IsConnectionExistsHelper(int sockfd)
    {
        auto iter = _connections.find(sockfd);
        if (iter == _connections.end())
            return false;
        else
            return true;
    }
    bool IsConnectionExists(const std::shared_ptr<Connection> &conn)
    {
        return IsConnectionExistsHelper(conn->GetSockFd());
    }
    bool IsConnectionExists(int sockfd)
    {
        return IsConnectionExistsHelper(sockfd);
    }
    bool IsConnectionEmpty()
    {
        return _connections.empty();
    }

    int LoopOnce(int timeout)
    {
        return _epoller_ptr->WaitEvents(_revs, revs_num, timeout);
    }

    void Dispatcher(int n) // 事件派发器
    {
        for (int i = 0; i < n; i++)
        {
            int sockfd = _revs[i].data.fd;      // 就绪的fd
            uint32_t revents = _revs[i].events; // 就绪的事件
            // 1. 将所有的异常处理，统一转化成IO错误 2. 所有的IO异常，统一转换成为一个异常处理函数
            if (revents & EPOLLERR)
                revents |= (EPOLLIN | EPOLLOUT); // 1. 将所有的异常处理，统一转化成IO错误
            if (revents & EPOLLHUP)
                revents |= (EPOLLIN | EPOLLOUT); // 1. 将所有的异常处理，统一转化成IO错误

            if (revents & EPOLLIN)
            {
                // 读事件就绪, 用不用区分是否异常?不用
                // 读事件就绪，还用不用区分是listenfd还是普通socketfd？不用
                if (IsConnectionExists(sockfd))
                    _connections[sockfd]->Recver();
            }
            if (revents & EPOLLOUT)
            {
                // 写事件就绪
                if (IsConnectionExists(sockfd))
                    _connections[sockfd]->Sender();
            }
        }
    }

public:
    Reactor()
        : _epoller_ptr(std::make_unique<Epoller>()),
          _isrunning(false)
    {
    }
    void Loop()
    {
        if (IsConnectionEmpty())
            return;

        _isrunning = true;
        int timeout = -1;
        while (_isrunning)
        {
            PrintConnection(); //debug
            int n = LoopOnce(timeout);
            Dispatcher(n);
        }
        _isrunning = false;
    }
    // 该接口要把所有的新连接添加到_connections，并且，写透到epoll内核中！！！！！
    void AddConnection(std::shared_ptr<Connection> &conn)
    {
        // 0. 不要重复添加
        if (IsConnectionExists(conn))
        {
            LOG(LogLevel::WARNING) << "conn is exists: " << conn->GetSockFd();
            return;
        }

        // 1. conn对应的fd和他要关心的事件，写透到内核中！
        uint32_t events = conn->GetEvent();
        int sockfd = conn->GetSockFd();
        _epoller_ptr->AddEvent(sockfd, events);

        // 2. 设置当前conn的拥有者回指指针
        conn->SetOwner(this);

        // 3. 将具体的connection添加到_connections
        _connections[sockfd] = conn;
    }
    void EnableReadWrite(int sockfd, bool enableread, bool enablewrite)
    {
        // 0. 不要重复添加
        if (!IsConnectionExists(sockfd))
        {
            LOG(LogLevel::WARNING) << "EnableReadWrite, conn is exists: " << sockfd;
            return;
        }

        // 1. 修改当前sockfd对应的connection关心的事件
        uint32_t new_event = (EPOLLET | (enableread ? EPOLLIN : 0) | (enablewrite ? EPOLLOUT:0));
        _connections[sockfd]->SetEvent(new_event);

        // 2. 写透到内核，调整sockfd对特定事件的关心
        _epoller_ptr->ModEvent(sockfd, new_event);
    }
    void DelConnection(int sockfd)
    {
        //1. epoll移除的时候，sockfd必须是合法的
        _epoller_ptr->DelEvent(sockfd);

        //2. 从_connections移除自己
        _connections.erase(sockfd);

        //3. 关闭不要的sockfd
        close(sockfd);

        LOG(LogLevel::INFO) << "client quit: " << sockfd;
    }
    void Stop()
    {
        _isrunning = false;
    }
    void PrintConnection()
    {
        std::cout << "当前Reactor正在进行管理的fd List:";
        for(auto &conn : _connections)
        {
            std::cout << conn.second->GetSockFd() << " ";
        }
        std::cout << "\r\n";
    }
    ~Reactor()
    {
    }

private:
    // 1. epoll模型
    std::unique_ptr<Epoller> _epoller_ptr;
    // 2. 是否启动
    bool _isrunning;
    // 3. 管理所有的connection，本质是管理未来所有我获取到的fd
    // fd : Connection
    std::unordered_map<int, std::shared_ptr<Connection>> _connections;
    // 4. 就绪的所有事件
    struct epoll_event _revs[revs_num];
};