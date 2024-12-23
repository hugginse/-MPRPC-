#ifndef _RPCPROVIDER_H_
#define _RPCPROVIDER_H_
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <string>
#include "mprpcapplication.h"
#include <functional>
#include <unordered_map>

#include "google/protobuf/service.h"
// 框架提供的专门服务发布rpc服务的网络对象
class RpcProvider
{
public:
    // 框架提供给外部服务的，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service* service);

    // 启动rpc服务节点，开始提供rpc远程网络调用服务远程
    void Run();
private:
    // 组合EventLoop
    muduo::net::EventLoop m_eventLoop;

    // 服务类型信息
    struct ServiceInfo
    {
        google::protobuf::Service* m_service;       // 保存服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_method_Map;    // 保存服务方法
    };

    // 存储注册成功的服务对象和其他服务方法的所有信息
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;

    // 新的socket连接回调
    void OnConnection(const muduo::net::TcpConnectionPtr&);
    
    // 已建立连接用户的读写事件回调
    void OnMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*, muduo::Timestamp);
};

#endif