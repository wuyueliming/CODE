#pragma once

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <memory>
#include <functional>
#include "Common.hpp"
#include "Connection.hpp"
#include "Log.hpp"
#include "InetAddr.hpp"

using namespace LogModule;

#define SIZE 1024

// 普通sockfd的封装
class Channel : public Connection
{
public:
    Channel(int sockfd, const InetAddr &client) : _sockfd(sockfd), _client_addr(client)
    {
        SetNonBlock(_sockfd);
    }

    // 问题1: 怎么保证我把本轮数据读取完毕？ while 循环 --- 本层只解决IO问题 --- done
    // 问题2：即便是你把本轮数据读完，你怎么知道数据就有完整的报文，如果不完整呢？如果是多个报文呢？粘报问题？反序列化 --- 引入协议的
    void Recver() override
    {
        // 我们读到的是字符串
        char buffer[SIZE];
        while (true)
        {
            buffer[0] = 0;                                            // 清空字符串
            ssize_t n = recv(_sockfd, buffer, sizeof(buffer) - 1, 0); // 非阻塞读取的
            if (n > 0)
            {
                buffer[n] = 0;
                _inbuffer += buffer; // 接受缓冲区中，入队列的过程
            }
            else if (n == 0)
            {
                Excepter();
                return;
            }
            else
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                {
                    break;
                }
                else if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    Excepter();
                    return;
                }
            }
        }
        LOG(LogLevel::DEBUG) << "Channel: Inbuffer:\n"
                             << _inbuffer;
        if (!_inbuffer.empty())
            _outbuffer += _handler(_inbuffer); // 和protocol相关的匿名函数里面！

        if (!_outbuffer.empty())
        {
            Sender(); // 最佳实践
            //GetOwner()->EnableReadWrite(_sockfd, true, true);
        }
       
    }
    void Sender() override
    {
        while (true)
        {
            ssize_t n = send(_sockfd, _outbuffer.c_str(), _outbuffer.size(), 0);
            if (n > 0)
            {
                _outbuffer.erase(0, n);
                if (_outbuffer.empty())
                    break;
            }
            else if (n == 0)
            {
                break;
            }
            else
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    break;
                if (errno == EINTR)
                    continue;
                else
                {
                    Excepter();
                    return;
                }
            }
        }

        // 1. 数据发送完毕
        // 2. 发送条件不具备
        if (!_outbuffer.empty())
        {
            // 开启对写事件的关心
            GetOwner()->EnableReadWrite(_sockfd, true, true);
        }
        else
        {
            GetOwner()->EnableReadWrite(_sockfd, true, false);
        }
    }
    void Excepter() override
    {
        // 所有的异常，都被我归一到了这个函数内部！！
        GetOwner()->DelConnection(_sockfd);
    }
    int GetSockFd() override
    {
        return _sockfd;
    }
    std::string &Inbuffer()
    {
        return _inbuffer;
    }
    void AppendOutBuffer(const std::string &out)
    {
        _outbuffer += out;
    }
    ~Channel()
    {
    }

private:
    int _sockfd;
    std::string _inbuffer; // 充当缓冲区，vector<char>
    std::string _outbuffer;
    InetAddr _client_addr;

    // handler_t _handler;
};