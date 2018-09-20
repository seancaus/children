//
// Created by Ziv on 2018/4/22.
//

#ifndef GATESERVER_APPLICATION_H
#define GATESERVER_APPLICATION_H

#include <memory>
#include <string>
#include "Singleton.h"

class Server;
class MessageManager;

class Application : public Singleton<Application> {

public:
    Application();
    virtual ~Application();

    void start();
    void onRecv(unsigned int msgId, std::string &uuid, std::string &msg);
    void send(std::string& uid, int pid, std::string& msg);

    void authPlayer(std::string &uid, std::string &uuid);

protected:

    std::shared_ptr<Server> _server;
};

#endif //GATESERVER_GATEMANAGER_H
