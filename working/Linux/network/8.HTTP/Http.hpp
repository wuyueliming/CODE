#pragma once

#include "Socket.hpp"
#include "TcpServer.hpp"
#include "Util.hpp"
#include "Log.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <functional>
#include <unordered_map>

using namespace SocketModule;
using namespace LogModule;

const std::string gspace = " ";
const std::string glinespace = "\r\n";
const std::string glinesep = ": ";

const std::string webroot = "./wwwroot";
const std::string homepage = "index.html";
const std::string page_404 = "/404.html";

class HttpRequest
{
public:
    HttpRequest() : _is_interact(false)
    {
    }
    std::string Serialize()
    {
        return std::string();
    }
    void ParseReqLine(std::string &reqline)
    {
        // GET / HTTP/1.1
        std::stringstream ss(reqline);
        ss >> _method >> _uri >> _version;
    }
    // 实现, 我们今天认为，reqstr是一个完整的http request string
    bool Deserialize(std::string &reqstr)
    {
        // 1. 提取请求行
        std::string reqline;
        bool res = Util::ReadOneLine(reqstr, &reqline, glinespace);
        LOG(LogLevel::DEBUG) << reqline;

        // 2. 对请求行进行反序列化
        ParseReqLine(reqline);

        if (_uri == "/")
            _uri = webroot + _uri + homepage; // ./wwwroot/index.html
        else
            _uri = webroot + _uri; // ./wwwroot/a/b/c.html

        LOG(LogLevel::DEBUG) << "_method: " << _method;
        LOG(LogLevel::DEBUG) << "_uri: " << _uri;
        LOG(LogLevel::DEBUG) << "_version: " << _version;
        const std::string temp = "?";
        auto pos = _uri.find(temp);
        if (pos == std::string::npos)
        {
            return true;
        }
        // _uri: ./wwwroot/login
        // username=zhangsan&password=123456
        _args = _uri.substr(pos + temp.size());
        _uri = _uri.substr(0, pos);
        _is_interact = true;

        // ./wwwroot/XXX.YYY
        return true;
    }
    std::string Uri()
    {
        return _uri;
    }
    bool isInteract()
    { 
        return _is_interact;
    }
    std::string Args()
    {
        return _args;
    }
    ~HttpRequest()
    {
    }

private:
    std::string _method;
    std::string _uri;
    std::string _version;

    std::unordered_map<std::string, std::string> _headers;
    std::string _blankline;
    std::string _text;

    std::string _args;
    bool _is_interact;
};

class HttpResponse
{
public:
    HttpResponse() : _blankline(glinespace), _version("HTTP/1.0")
    {
    }
    // 实现: 成熟的http，应答做序列化，不要依赖任何第三方库！
    std::string Serialize()
    {
        std::string status_line = _version + gspace + std::to_string(_code) + gspace + _desc + glinespace;
        std::string resp_header;
        for (auto &header : _headers)
        {
            std::string line = header.first + glinesep + header.second + glinespace;
            resp_header += line;
        }

        return status_line + resp_header + _blankline + _text;
    }
    void SetTargetFile(const std::string &target)
    {
        _targetfile = target;
    }
    void SetCode(int code)
    {
        _code = code;
        switch (_code)
        {
        case 200:
            _desc = "OK";
            break;
        case 404:
            _desc = "Not Found";
            break;
        case 301:
            _desc = "Moved Permanently";
            break;
        case 302:
            _desc = "See Other";
            break;
        default:
            break;
        }
    }
    void SetHeader(const std::string &key, const std::string &value)
    {
        auto iter = _headers.find(key);
        if (iter != _headers.end())
            return;
        _headers.insert(std::make_pair(key, value));
    }
    std::string Uri2Suffix(const std::string &targetfile)
    {
        // ./wwwroot/a/b/c.html
        auto pos = targetfile.rfind(".");
        if (pos == std::string::npos)
        {
            return "text/html";
        }

        std::string suffix = targetfile.substr(pos);
        if (suffix == ".html" || suffix == ".htm")
            return "text/html";
        else if (suffix == ".jpg")
            return "image/jpeg";
        else if (suffix == "png")
            return "image/png";
        else
            return "";
    }

    bool MakeResponse()
    {
        if (_targetfile == "./wwwroot/favicon.ico")
        {
            LOG(LogLevel::DEBUG) << "用户请求: " << _targetfile << "忽略它";
            return false;
        }
        if (_targetfile == "./wwwroot/redir_test")
        {
            SetCode(301);
            SetHeader("Location", "https://www.qq.com/");
            return true;
        }
        int filesize = 0;
        bool res = Util::ReadFileContent(_targetfile, &_text); // 浏览器请求的资源，一定会存在吗？出错呢？
        if (!res)
        {
            _text = "";
            LOG(LogLevel::WARNING) << "client want get : " << _targetfile << " but not found";
            SetCode(404);
            _targetfile = webroot + page_404;
            filesize = Util::FileSize(_targetfile);
            Util::ReadFileContent(_targetfile, &_text);
            std::string suffix = Uri2Suffix(_targetfile);
            SetHeader("Content-Type", suffix);
            SetHeader("Content-Length", std::to_string(filesize));
            // SetCode(302);
            // SetHeader("Location", "http://8.137.19.140:8080/404.html");
            // return true;
        }
        else
        {
            LOG(LogLevel::DEBUG) << "读取文件: " << _targetfile;
            SetCode(200);
            filesize = Util::FileSize(_targetfile);
            std::string suffix = Uri2Suffix(_targetfile);
            SetHeader("Conent-Type", suffix);
            SetHeader("Content-Length", std::to_string(filesize));
            SetHeader("Set-Cookie", "username=zhangsan;");
            // SetHeader("Set-Cookie", "passwd=123456;");
        }
        return true;
    }
    void SetText(const std::string &t)
    {
        _text = t;
    }
    bool Deserialize(std::string &reqstr)
    {
        return true;
    }
    ~HttpResponse() {}

    // private:
public:
    std::string _version;
    int _code;         // 404
    std::string _desc; // "Not Found"

    std::unordered_map<std::string, std::string> _headers;
    std::vector<std::string> cookie;
    std::string _blankline;
    std::string _text;

    // 其他属性
    std::string _targetfile;
};

using http_func_t = std::function<void(HttpRequest &req, HttpResponse &resp)>;

// 1. 返回静态资源
// 2. 提供动态交互的能力
class Http
{
public:
    Http(uint16_t port) : tsvrp(std::make_unique<TcpServer>(port))
    {
    }
    void HandlerHttpRquest(std::shared_ptr<Socket> &sock, InetAddr &client)
    {
        // 收到请求
        std::string httpreqstr;
        // 假设：概率大，读到了完整的请求
        // bug!
        int n = sock->Recv(&httpreqstr); // 浏览器给我发过来的是一个大的http字符串, 其实我们的recv也是有问题的。tcp是面向字节流的.
        if (n > 0)
        {
            std::cout << "##########################" << std::endl;
            std::cout << httpreqstr;
            std::cout << "##########################" << std::endl;
            // 对报文完整性进行审核 -- 缺
            // 所以，今天，我们就不在担心，用户访问一个服务器上不存在的资源了.
            // 我们更加不担心，给用户返回任何网页资源(html, css, js, 图片，视频)..., 这种资源，静态资源！！
            HttpRequest req;
            HttpResponse resp;
            req.Deserialize(httpreqstr);
            if (req.isInteract())
            {
                // _uri: ./wwwroot/login
                if (_route.find(req.Uri()) == _route.end())
                {
                    // SetCode(302)
                }
                else
                {
                    _route[req.Uri()](req, resp);
                    std::string response_str = resp.Serialize();
                    sock->Send(response_str);
                }
            }
            else
            {
                resp.SetTargetFile(req.Uri());
                if (resp.MakeResponse())
                {
                    std::string response_str = resp.Serialize();
                    sock->Send(response_str);
                }
            }

            // HttpResponse resp;
            // resp._version = "HTTP/1.1";
            // resp._code = 200; // success
            // resp._desc = "OK";
            // //./wwwroot/a/b/c.html
            // LOG(LogLevel::DEBUG) << "用户请求: " << filename;
            // bool res = Util::ReadFileContent(filename, &(resp._text)); // 浏览器请求的资源，一定会存在吗？出错呢？
            // (void)res;
        }

// #ifndef DEBUG
// #define DEBUG
#ifdef DEBUG
        // 收到请求
        std::string httpreqstr;
        // 假设：概率大，读到了完整的请求
        sock->Recv(&httpreqstr); // 浏览器给我发过来的是一个大的http字符串, 其实我们的recv也是有问题的。tcp是面向字节流的.
        std::cout << httpreqstr;

        // 直接构建http应答. 内存级别+固定
        HttpResponse resp;
        resp._version = "HTTP/1.1";
        resp._code = 200; // success
        resp._desc = "OK";

        std::string filename = webroot + homepage; // "./wwwroot/index.html";
        bool res = Util::ReadFileContent(filename, &(resp._text));
        (void)res;
        std::string response_str = resp.Serialize();
        sock->Send(response_str);
#endif
        // 对请求字符串，进行反序列化
    }
    void Start()
    {
        tsvrp->Start([this](std::shared_ptr<Socket> &sock, InetAddr &client)
                     { this->HandlerHttpRquest(sock, client); });
    }
    void RegisterService(const std::string name, http_func_t h)
    {
        std::string key = webroot + name; // ./wwwroot/login
        auto iter = _route.find(key);
        if (iter == _route.end())
        {
            _route.insert(std::make_pair(key, h));
        }
    }
    ~Http()
    {
    }

private:
    std::unique_ptr<TcpServer> tsvrp;
    std::unordered_map<std::string, http_func_t> _route;
};
