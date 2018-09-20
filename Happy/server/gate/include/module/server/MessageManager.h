//
// Created by Ziv on 2018/4/4.
//

#ifndef MAHJONGSERVER_SERVICEMANAGER_H
#define MAHJONGSERVER_SERVICEMANAGER_H

#include <map>
#include <memory>

using namespace std;

class ModuleListener;

class MessageManager {

public:

    MessageManager();
    virtual ~MessageManager();

    void registerHandler(int packId, shared_ptr<ModuleListener>);
    void dispatchMessage(int packId, std::string &uid, string &msg);

protected:

    map<int,shared_ptr<ModuleListener>> _handlers;

};


#endif //MAHJONGSERVER_SERVICEMANAGER_H
