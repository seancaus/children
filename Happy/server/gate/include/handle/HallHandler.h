//
// Created by Ziv on 2018/4/20.
//

#ifndef GATESERVER_HALLMESSAGEHANDLER_H
#define GATESERVER_HALLMESSAGEHANDLER_H

#include "ModuleListener.h"

class HallServer;

class HallHandler : public ModuleListener
{

public:
    HallHandler();
    virtual ~HallHandler();

    virtual void handleMessage(std::string& uid, std::string& msg) override;

protected:

    std::shared_ptr<HallServer> _hallServer;

};


#endif //GATESERVER_HALLHANDLER_H
