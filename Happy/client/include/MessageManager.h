//
// Created by Ziv on 2018/4/4.
//

#ifndef MAHJONGSERVER_SERVICEMANAGER_H
#define MAHJONGSERVER_SERVICEMANAGER_H

#include <map>
#include <memory>
#include <vector>

using namespace std;

class MessageHandler;

class MessageManager {

public:

    MessageManager();
    virtual ~MessageManager();

    void registerListener(unsigned int msgId, shared_ptr<MessageHandler> service);
    void dispatchMessage();

    void pushMessage(unsigned int msgId, string &msg);
    void clearMessage();

protected:

    vector<pair<unsigned int,string>>   _messages;
    map<int,shared_ptr<MessageHandler>> _listeners;

};


#endif //MAHJONGSERVER_SERVICEMANAGER_H
