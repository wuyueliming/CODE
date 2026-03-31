#include "common.h"
#include "InetAddr.hpp"
#include "Log.hpp"
#include <functional>

using namespace LogModule;

using func_t = std::function<std::string(const std::string &, const InetAddr &)>;

class TCPserver
{
public:
     TCPserver(uint16_t port, func_t func) : _localAddr("0.0.0.0", port),
                                             _func(func)
     {
          // signal(SIGCHLD, SIG_IGN);忽略子进程退出的信号，自动回收资源
     }
     ~TCPserver()
     {
     }

     void Init()
     {
          // 创建listen socket
          _listenfd = socket(AF_INET, SOCK_STREAM, 0);
          if (_listenfd < 0)
          {
               LOG(LogLevel::FATAL) << "sockrt error";
               exit(SOCKET_ERR);
          }
          LOG(LogLevel::INFO) << "sockrt success: " << _listenfd;

          // bind 本地地址
          int ret = bind(_listenfd, (const sockaddr *)&_localAddr.Addr(), _localAddr.AddrLen());
          if (ret < 0)
          {
               LOG(LogLevel::ERROR) << "bind error";
               exit(BIND_ERR);
          }
          LOG(LogLevel::INFO) << "bind success";

          // 开始监听
          ret = listen(_listenfd, 5);
          if (ret < 0)
          {
               LOG(LogLevel::ERROR) << "listen error";
               exit(LISTEN_ERR);
          }
          LOG(LogLevel::INFO) << "listen success";
     }

     void serve(int sockfd, InetAddr client)
     {
          char buffer[1024];
          while (true)
          {    //BUG？ 使用tcp面向字节流，需要自己判断是否收到的是完整报文。
               int ret = read(sockfd, buffer, sizeof(buffer) - 1);
               if (ret < 0)
               {
                    LOG(LogLevel::ERROR) << "read error";
                    exit(READ_ERR);
               }
               else if (ret == 0)
               {
                    LOG(LogLevel::INFO) << "用户退出...";
                    exit(FINE);
               }
               else
               {
                    buffer[ret] = 0;
                    std::string msg(buffer);
                    LOG(LogLevel::INFO) << "client message > " << msg;
                    std::string res = _func(msg, client);
                    res += "\n";
                    write(sockfd, res.c_str(), res.size());
               }
          }
     }

     // 长服务(多进程、多线程)：游戏，音乐...
     void start()
     {
          if (_isRunning)
               return;

          _isRunning = true;
          // 每次循环只处理一个ip的请求?
          while (_isRunning) // 主进程获取连接，处理交给子进程
          {
               // 获取连接
               struct sockaddr_in peer;
               socklen_t len;
               int connectfd = accept(_listenfd, (struct sockaddr *)&peer, &len);
               if (connectfd < 0)
               {
                    LOG(LogLevel::ERROR) << "accept error";
                    exit(ACCEPT_ERR);
               }
               InetAddr clientAddr(peer);
               LOG(LogLevel::INFO) << "用户(" << clientAddr.IP() << ":" << clientAddr.Port() << ") 已连接...";

               // serve(connectfd,clientAddr);
               //  version1 --- 多进程
               pid_t pid = fork();
               if (pid < 0)
               {
                    LOG(LogLevel::FATAL) << "fork error";
                    exit(FORK_ERR);
               }
               else if (pid == 0)// 子进程
               {                      
                    close(_listenfd); // 关闭不用的文件
                    if (fork()>0)// 创建孙子进程，子进程退出
                    { 
                         LOG(LogLevel::DEBUG) << "子进程退出";
                         exit(FINE);
                    }
                    // 孙子进程被1接管，自动回收,孙子来服务客户端
                    LOG(LogLevel::DEBUG) << "孙子进程服务用户：" << clientAddr.StringAddr();
                    serve(connectfd, clientAddr);
                    exit(FINE);
               }
               else// 父进程
               {                                        
                    int rid = waitpid(pid, nullptr, 0); // 子进程立马就退，不会阻塞很久。
                    close(connectfd);
                    LOG(LogLevel::DEBUG) << "父进程继续获取连接";
               }
          }
          _isRunning = false;
     }

     // 短服务(线程池)：网页
     void start1()
     {
     }

private:
     int _listenfd = -1;
     InetAddr _localAddr;
     bool _isRunning = false;

     func_t _func;
};
