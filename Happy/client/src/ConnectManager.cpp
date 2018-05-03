//
// Created by Ziv on 2018/4/30.
//

#include <thread>
#include <handler/HallHandler.h>
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