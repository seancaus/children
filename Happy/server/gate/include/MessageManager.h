//
// Created by Ziv on 2018/4/4.
//

#ifndef MAHJONGSERVER_SERVICEMANAGER_H
#define MAHJONGSERVER_SERVICEMANAGER_H

#include <map>
#include <memory>

using namespace std;

class MessageHandler;

class MessageManager {

public:

    MessageManager();
    virtual ~MessageManager();

    void registerListener(unsigned int packId, shared_ptr<MessageHandler> service);
    void dispatchMessage(unsigned int packId, string &msg);

protected:

    map<int,shared_ptr<MessageHandler>> _listeners;

};


#endif //MAHJONGSERVER_SERVICEMANAGER_H
