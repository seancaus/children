//
// Created by Ziv on 2018/3/28.
//
#include <cassert>
#include "Packet.h"

using namespace std;

struct Pack{
    unsigned int packId;
    unsigned int length;
};

Packet::Packet() {

}

Packet::~Packet() {

}

void Packet::pack(unsigned int packId, std::string &data, std::string &msg) {
    assert(packId > 0);

    Pack pack{packId, (unsigned int)data.length()};
    char *temp = new char[sizeof(Pack) + data.length()];
    memcpy(temp, &pack, sizeof(Pack));
    memcpy(temp + sizeof(Pack), data.data(), data.length());

    msg.assign(temp,sizeof(Pack) + data.length());
    delete []temp;
}

unsigned int Packet::unpack(string &data, std::string &msg) {
    if( data.length() < sizeof(Pack) )return 0;

    Pack pack;
    memcpy(&pack, data.data(), sizeof(Pack));
    if( data.length() < pack.length + sizeof(Pack) ) return 0;

    msg.assign(data.data() + sizeof(Pack), pack.length);
    data.erase(0, pack.length + sizeof(Pack));
    return pack.packId;
}