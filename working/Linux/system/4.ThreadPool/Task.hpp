#pragma once
#include <iostream>
#include <unistd.h>
#include <functional>
#include "Log.hpp"

using namespace LogModule;

// 任务形式2
// 我们定义了一个任务类型，返回值void，参数为空
using task_t = std::function<void()>;

void Download()
{
   LOG(LogLevel::DEBUG) << "我是一个下载任务...";
}

// 任务形式1
class Task
{
public:
    Task(){}
    Task(int x, int y):_x(x), _y(y)
    {
    }

    void operator() (){//如果；线程池中想要更丰富的任务形式，可以不用修改这个，还是保持返回void，参数空。只需要修改成员变量
        Execute();     //ThreadPool线程池不适合手动传参，适合用这种包装的task
    }
    void Execute()
    {
        _result = _x + _y;
    }
    int X() { return _x; }
    int Y() { return _y; }
    int Result()
    {
        return _result;
    }
private:
    //输入参数
    int _x;
    int _y;
    //输出参数
    int _result;
};