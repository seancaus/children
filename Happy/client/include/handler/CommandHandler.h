//
// Created by Ziv on 2018/4/8.
//

#ifndef NETWORK_COMMANDHANDLER_H
#define NETWORK_COMMANDHANDLER_H

#include "MessageHandler.h"

class CommandHandler :public MessageHandler{

public:
    virtual void handleMessage(string &msg) override;
};


#endif //NETWORK_COMMANDHANDLER_H
