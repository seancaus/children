//
// Created by Ziv on 2018/4/4.
//

#ifndef MAHJONGSERVER_GAMESERVICE_H
#define MAHJONGSERVER_GAMESERVICE_H

#include <string>
#include "MessageHandler.h"

using namespace std;

class TableManager;

class TableHandler : public MessageHandler {

public:

    TableHandler();
    virtual ~TableHandler();

    virtual void handleMessage(string &msg) override;

protected:

    shared_ptr<TableManager> _tableManager;

};


#endif //MAHJONGSERVER_GAMESERVICE_H
