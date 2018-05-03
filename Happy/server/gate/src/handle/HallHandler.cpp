//
// Created by Ziv on 2018/4/20.
//

#include <memory>
#include "handle/HallHandler.h"
#include "module/hall/HallServer.h"

using namespace std;

HallHandler::HallHandler()
    :_hallServer(make_shared<HallServer>())
{

}

HallHandler::~HallHandler() {

}


void HallHandler::handleMessage(std::string& uid, std::string& msg) {
    _hallServer->handleMessage(uid,msg);
}