#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"

/*
UserService原来是一个本地服务，提供了两个进程内的本地方法，Login和GetFriendLists
*/
class UserService : public fixbug::UserServiceRpc   // 使用再rpc服务发布端（RPC服务提供者）
{
public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name: " << name << " pwd: " << std::endl;
        return true;
    }

    /*
    1. caller ===> Login(LoginRequest) => muduo => callee
    2. callee ===> Login(LoginRequest) => 交到下面重写的Login方法上
    */
    // 重写基类UserServiceRpc的虚函数，下面这些方法都是框架之直接调用
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了请求参数LoginRequest，业务取出相应数据做本地业务
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 做本地业务
        bool loginresult = Login(name, pwd);    

        // 把响应写入 包括错误码、错误消息、返回值
        fixbug::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(loginresult);
    
        // 执行回调操作  执行响应对象数据的序列化和网络发送（由框架来完成）
        done->Run();
    }
};

int main(int argc, char **argv)
{
    // 调用框架初始化操作 provider -i config.conf
    MprpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象。把UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new UserService());

    // 启动一个rpc服务节点.  Run以后，进程进入阻塞状态，等待远程rpc调用请求
    provider.Run();
    return 0;
}