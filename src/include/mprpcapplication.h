#ifndef _MPRPCAPPLICATION_H_
#define _MPRPCAPPLICATION_H_

// mprpc框架的基础类
class MprpcApplication
{
public:
    static void Init(int argc, char** argv);
    static MprpcApplication& GetInstance();
private:
    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;

};

#endif
