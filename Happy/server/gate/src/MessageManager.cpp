//
// Created by Ziv on 2018/4/4.
//

#include <iostream>

#include <MessageManager.h>
#include "ModuleListener.h"

using namespace std;

MessageManager::MessageManager() {

}

MessageManager::~MessageManager() {

}

void MessageManager::registerHandler(unsigned int msgId, shared_ptr <ModuleListener> handler) {
    _handlers.insert(make_pair(msgId, handler));
}

void MessageManager::dispatchMessage(unsigned int msgId, string &uid, string &msg) {
    auto listener = _handlers.find(msgId);
    if(listener == _handlers.end()){
        cout << "can't find the listener for msgId:" << msgId << endl;
        return;
    }

    listener->second->handleMessage(uid,msg);
}

