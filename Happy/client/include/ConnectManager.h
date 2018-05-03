//
// Created by Ziv on 2018/4/30.
//

#ifndef NETWORK_CONNECTMANAGER_H
#define NETWORK_CONNECTMANAGER_H

#include <map>
#include "Singleton.h"
#include "IConnector.h"


class MessageManager;

class ConnectManager : public Singleton<ConnectManager>
{

public:

    ConnectManager();

    void connect(std::string ip = "127.0.0.1", unsigned int port = 9999);
    void onRecv(unsigned int msgId, std::string &msg);
    void start(bool wait = false);
    void send(unsigned int msgId, std::string &msg);
    void tick();

protected:

    void registerDefHandler();

protected:

    std::map<int, std::shared_ptr<IConnector>>     _mapConnector;
    std::shared_ptr<MessageManager>                  _msgManager;
};


#endif //NETWORK_NEWWORKMANAGER_H
