//
// Created by Ziv on 2018/5/2.
//

#ifndef NETWORK_ICONNECTOR_H
#define NETWORK_ICONNECTOR_H

#include <string>

class IConnector
{
public:
    virtual void connect() = 0;
    virtual void close() = 0;

    virtual void send(std::string& msg) = 0;
    virtual void receive() = 0;
};

#endif //NETWORK_ICONNECTOR_H
