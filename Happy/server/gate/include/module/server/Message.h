//
// Created by Ziv on 2018/4/21.
//

#ifndef GATESERVER_MESSAGE_H
#define GATESERVER_MESSAGE_H

#include <string>

namespace uvw{
    class TcpHandle;
}

class Message {

public:
    Message(uvw::TcpHandle& handle,std::string msg);
    virtual ~Message();
protected:

    std::string _msg;
    uvw::TcpHandle& _client;

};


#endif //GATESERVER_MESSAGE_H
