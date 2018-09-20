//
// Created by Ziv on 2018/4/22.
//

#include "Application.h"
#include "module/server/Server.h"
#include "PlayerManager.h"
#include "module/server/Packet.h"
#include "module/server/MessageManager.h"
#include "handle/Handler.h"

using namespace std;

template <> Application* Singleton<Application>::instance = nullptr;

Application::Application()
        : _server(make_shared<Server>())
{
}

Application::~Application()
{
}

void Application::start()
{
//    _msgManager->registerHandler(Handler_Hall, make_shared<HallHandler>());
//    _msgManager->registerHandler(Handler_Room, make_shared<RoomHandler>());

    _server->start("127.0.0.1",9999,make_shared<Packet>(),make_shared<MessageManager>());
}

void Application::onRecv(unsigned int msgId, std::string& uuid, std::string &msg)
{
//    _msgManager->dispatchMessage(msgId, uuid, msg);
}

void Application::send(std::string& uid, int msgId, std::string &msg)
{
    _server->send(uid,msgId,msg);
}

void Application::authPlayer(std::string &uid, std::string &uuid)
{
    _server->authClient(uuid, uid);
}