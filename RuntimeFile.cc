#include"RuntimeFile.h"

RuntimeFile::RuntimeFile()
{
    usrIndex = 0;
    commIndex = 0;
    orderIndex =  0;
    ReadToUsrs();
    ReadToComms();
    ReadToOrders();
}

RuntimeFile::~RuntimeFile()
{

}

void RuntimeFile::AddUser(string name, string passwd)
{
    
}

bool RuntimeFile::find(string name) const
{

}

LogFlag RuntimeFile::matching(string name, string passwd) const
{

}

bool RuntimeFile::modifyComm()
{

}

bool RuntimeFile::modifyOrder()
{

}

bool RuntimeFile::modifyUsr()
{

}

void RuntimeFile::ShowCommodities() const
{

}

void RuntimeFile::ShowOrders() const
{

}

void RuntimeFile::ShowUsrs() const
{

}

void RuntimeFile::WriteCommsFile() const
{

}

void RuntimeFile::WriteOrdersFile() const
{

}

void RuntimeFile::WriteUsrsFile() const
{

}