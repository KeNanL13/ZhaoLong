#include "cable.h"
#include <QDebug>

Cable::Cable(QObject *parent) : QObject(parent)
{
   zhaolongFunctionInitialize();
   qDebug()<<"基类的构造函数";
}

Cable::~Cable()
{
    zhaolongFunctionTerminate();
}

bool Cable::IsParametersComplete()
{
    if(parameters.size()!=m_size)
    {
        return false;
    }
    return true;
}
