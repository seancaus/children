//
// Created by Ziv on 2018/3/28.
//
#include <cassert>
#include "Packet.h"

using namespace std;

struct Pack{
    unsigned int msgId;
    unsigned int length;
};

void Packet::pack(unsigned int msgId, std::string &data, std::string &out) {
    assert(msgId >= 0);

    Pack pack{msgId, (unsigned int)data.length()};
    char *temp = new char[sizeof(Pack) + data.length()];
    memcpy(temp, &pack, sizeof(Pack));
    memcpy(temp + sizeof(Pack), data.data(), data.length());

    out.assign(temp, sizeof(Pack) + data.length());
    delete []temp;
}

unsigned int Packet::unpack(string &data, std::string &out) {
    if( data.length() < sizeof(Pack) ) return -1;

    Pack pack;
    memset(&pack,0, sizeof(Pack));
    memcpy(&pack, data.data(), sizeof(Pack));
    if( data.length() < pack.length + sizeof(Pack) ) return -1;

    out.assign(data.data() + sizeof(Pack), pack.length);
    data.erase(0, pack.length + sizeof(Pack));
    return pack.msgId;
}