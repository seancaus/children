//
// Created by Ziv on 2018/4/4.
//

#include <iostream>

#include <module/server/MessageManager.h>
#include "ModuleListener.h"

using namespace std;

MessageManager::MessageManager() {

}

MessageManager::~MessageManager() {

}

void MessageManager::registerHandler(int packId, shared_ptr <ModuleListener> handler) {
    _handlers.insert(make_pair(packId, handler));
}

void MessageManager::dispatchMessage(int packId, string &uid, string &msg) {
    auto listener = _handlers.find(packId);
    if(listener == _handlers.end()){
        cout << "can't find the listener for msgId:" << packId << endl;
        return;
    }

    listener->second->handleMessage(uid,msg);
}

