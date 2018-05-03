//
// Created by Ziv on 2018/3/28.
//

#ifndef MAHJONGSERVER_PACKET_H
#define MAHJONGSERVER_PACKET_H

#include <string>

class Packet {

public:
    virtual void pack(unsigned int typeId, std::string &data, std::string &out);
    virtual unsigned int unpack(std::string &data, std::string &out);
};


#endif //MAHJONGSERVER_PACKET_H
