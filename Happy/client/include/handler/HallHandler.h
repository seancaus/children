//
// Created by Ziv on 2018/4/22.
//

#ifndef NETWORK_HALLHANDLER_H
#define NETWORK_HALLHANDLER_H


#include "MessageHandler.h"

class HallHandler : public MessageHandler{

public:


    virtual void handleMessage(string &msg) override ;


};


#endif //NETWORK_HALLHANDLER_H
