#ifndef _MPRPCAPPLICATION_H_
#define _MPRPCAPPLICATION_H_

#include "mprpcconfig.h"

// mprpc框架的基础类
class MprpcApplication
{
public:
    static void Init(int argc, char** argv);
    static MprpcApplication& GetInstance();
private:
    static MprpcConfig m_config; 


    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;

};

#endif
