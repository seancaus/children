//
// Created by Ziv on 2018/4/21.
//

#include "module/server/Message.h"


Message::Message(uvw::TcpHandle & handle,std::string msg)
        : _client(handle)
        ,_msg(msg)
{

}

Message::~Message() {

}

