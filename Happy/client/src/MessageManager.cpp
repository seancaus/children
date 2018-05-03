//
// Created by Ziv on 2018/4/4.
//

#include <iostream>

#include <MessageManager.h>
#include "MessageHandler.h"

using namespace std;

MessageManager::MessageManager() {

}

MessageManager::~MessageManager() {

}

void MessageManager::registerListener(unsigned int msgId, shared_ptr <MessageHandler> service) {
    _listeners.insert(make_pair(msgId,service));
}

void MessageManager::pushMessage(unsigned int msgId, string &msg) {
    _messages.push_back(make_pair(msgId,msg));

    this->dispatchMessage();
}

void MessageManager::clearMessage()
{
    _messages.clear();
}

void MessageManager::dispatchMessage() {
    while( !_messages.empty() ){
        auto pair = _messages.erase(_messages.begin());

        auto listener = _listeners.find(pair->first);
        if(listener == _listeners.end()){
            cout << "can't find the listener for msgId:" << pair->first << endl;
            continue;
        }

        listener->second->handleMessage(pair->second);
    }
}



