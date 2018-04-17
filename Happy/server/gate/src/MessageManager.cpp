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

void MessageManager::registerListener(unsigned int packId, shared_ptr <MessageHandler> service) {
    _listeners.insert(make_pair(packId,service));
}

void MessageManager::dispatchMessage(unsigned int packId, string &msg) {
    auto listener = _listeners.find(packId);
    if(listener == _listeners.end()){
        cout << "can't find the listener for packid:" << packId << endl;
        return;
    }

    listener->second->handleMessage(msg);
}

