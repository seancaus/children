//
// Created by Ziv on 2018/4/22.
//

#include "Root.h"
#include "Server.h"
#include "PlayerManager.h"
#include "MessageManager.h"
#include "handle/Handler.h"

using namespace std;

template <> Root* Singleton<Root>::instance = nullptr;

Root::Root()
        : _msgManager(make_shared<MessageManager>())
        ,_server(make_shared<Server>())
{
    _server->set_handler(std::bind(&Root::onRecv, this, placeholders::_1, placeholders::_2, placeholders::_3));
}

Root::~Root()
{
}

void Root::start()
{
    _msgManager->registerHandler(Handler_Hall, make_shared<HallHandler>());
    _msgManager->registerHandler(Handler_Room, make_shared<RoomHandler>());

    _server->start();
}

void Root::onRecv(unsigned int msgId, std::string& uuid, std::string &msg)
{
    _msgManager->dispatchMessage(msgId, uuid, msg);
}

void Root::send(std::string& uid, int msgId, std::string &msg)
{
    _server->send(uid,msgId,msg);
}

void Root::authPlayer(std::string &uid, std::string &uuid)
{
    _server->authClient(uuid, uid);
}