//
// Created by Ziv on 2018/4/6.
//

#ifndef NETWORK_TABLELISTENER_H
#define NETWORK_TABLELISTENER_H

#include "../MessageHandler.h"

class TableHandler :public MessageHandler
{

public:
    virtual void handleMessage(string &msg) override;
};


#endif //NETWORK_TABLELISTENER_H
