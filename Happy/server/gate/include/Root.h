//
// Created by Ziv on 2018/4/22.
//

#ifndef GATESERVER_ROOT_H
#define GATESERVER_ROOT_H

#include <memory>
#include <string>
#include "Singleton.h"

class Server;
class MessageManager;

class Root : public Singleton<Root> {

public:
    Root();
    virtual ~Root();

    void start();
    void onRecv(unsigned int msgId, std::string &uuid, std::string &msg);
    void send(std::string& uid, int pid, std::string& msg);

    void authPlayer(std::string &uid, std::string &uuid);

protected:

    std::shared_ptr<Server> _server;
    std::shared_ptr<MessageManager> _msgManager;
};

#endif //GATESERVER_GATEMANAGER_H
