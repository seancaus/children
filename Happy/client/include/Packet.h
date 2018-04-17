//
// Created by Ziv on 2018/3/28.
//

#ifndef MAHJONGSERVER_PACKET_H
#define MAHJONGSERVER_PACKET_H

#include <string>

class Packet {

public:
    Packet();
    virtual ~Packet();

    virtual void pack(unsigned int packId, std::string &data, std::string &msg);
    virtual unsigned int unpack(std::string &data, std::string &msg);


};


#endif //MAHJONGSERVER_PACKET_H
