#pragma once

#include <iostream>
#include <string>
#include "InetAddr.hpp"

// 封装fd，保证给每一个fd一套缓冲
class Reactor;
class Connection;

using handler_t = std::function<std::string (std::string &)>;

// 基类
class Connection
{
public:
    Connection():_events(0), _owner(nullptr)
    {
    }
    void SetEvent(const uint32_t &events)
    {
        _events = events;
    }
    uint32_t GetEvent()
    {
        return _events;
    }
    void SetOwner(Reactor *owner)
    {
        _owner = owner;
    }
    Reactor *GetOwner()
    {
        return _owner;
    }
    virtual void Recver() = 0;
    virtual void Sender() = 0;
    virtual void Excepter() = 0;
    virtual int GetSockFd() = 0;

    void RegisterHandler(handler_t handler)
    {
        _handler = handler;
    }
    ~Connection()
    {
    }

private:
    // 关心事件
    uint32_t _events;

    // 回指指针
    Reactor *_owner;

public:
    handler_t _handler; // 基类中定义了一个回调函数
};