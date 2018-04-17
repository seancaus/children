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

void MessageManager::pushMessage(unsigned int packId, string &msg) {
    _messages.push_back(make_pair(packId,msg));
}


void MessageManager::dispatchMessage() {
    while( !_messages.empty() ){
        auto pair = _messages.erase(_messages.begin());

        auto listener = _listeners.find(pair->first);
        if(listener == _listeners.end()){
            cout << "can't find the listener for packid:" << pair->first << endl;
            continue;
        }

        listener->second->handleMessage(pair->second);
    }
}



