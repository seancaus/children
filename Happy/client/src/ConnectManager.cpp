//
// Created by Ziv on 2018/4/30.
//

#include <thread>
#include <handler/HallHandler.h>
#include <iostream>
#include "TCPConnector.h"
#include "ConnectManager.h"
#include "MessageManager.h"
#include "handler/ModuleDef.h"

using namespace std;

template <> ConnectManager* Singleton<ConnectManager>::instance = nullptr;

ConnectManager::ConnectManager():
        _msgManager(make_shared<MessageManager>())
{
//    _connector->set_handler(std::bind(&ConnectManager::onRecv, this, placeholders::_1, placeholders::_2));
}

int ConnectManager::createConnect(string ip, unsigned int port)
{
    int connectId = 0;
    auto connect = make_shared<TCPConnector>(ip, port);
    _mapConnector.insert(make_pair(connectId, connect));
    return connectId;
}

void ConnectManager::closeConnect(int connectId)
{
    auto iter = _mapConnector.find(connectId);
    if( iter == _mapConnector.end() )
    {
        cout << "don't have connect for connectId:" << connectId << endl;
        return;
    }

    auto connect = _mapConnector.erase(iter)->second;
    connect->close();
}

void ConnectManager::send(int connectId, std::string &msg)
{
    auto iter = _mapConnector.find(connectId);
    if( iter == _mapConnector.end() )
    {
        cout << "don't have connect for connectId:" << connectId << endl;
        return;
    }

    auto connect = _mapConnector.erase(iter)->second;
    connect->send(msg);
}

void ConnectManager::registerDefHandler()
{
    _msgManager->clearMessage();
    _msgManager->registerListener(Handler_Hall,make_shared<HallHandler>());
}

void ConnectManager::connect(string ip, unsigned int port)
{
//    _connector->connect(ip, port);
}

void ConnectManager::onRecv(unsigned int msgId, std::string &msg)
{
    _msgManager->pushMessage(msgId, msg);
}

void ConnectManager::start(bool wait)
{
//    thread conThread([&](){_connector->loop();});
//    if(wait) conThread.join();
}

void ConnectManager::send(unsigned int msgId, std::string &msg)
{
//    _connector->send(msgId, msg);
}

void ConnectManager::tick()
{
    _msgManager->dispatchMessage();
}