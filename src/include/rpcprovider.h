#ifndef _RPCPROVIDER_H_
#define _RPCPROVIDER_H_

#include "google/protobuf/service.h"
// 框架提供的专门服务发布rpc服务的网络对象
class RpcProvider
{
public:
    // 框架提供给外部服务的，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service* service);

    // 启动rpc服务节点，开始提供rpc远程网络调用服务远程
    void Run();
};

#endif