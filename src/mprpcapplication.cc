#include "mprpcapplication.h"

void Init(int argc, char **argv) 
{

}

MprpcApplication& MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}