//
// Created by Ziv on 2018/3/28.
//
#include <cassert>
#include <cstring>
#include "module/server/Packet.h"

using namespace std;

struct Pack
{
    int packId;
    unsigned int length;
};

void Packet::pack(int packId, std::string &data, std::string &out) {
    assert(packId >= 0);

    Pack pack{packId, (unsigned int)data.length()};
    char *temp = new char[sizeof(Pack) + data.length()];
    memcpy(temp, &pack, sizeof(Pack));
    memcpy(temp + sizeof(Pack), data.data(), data.length());

    out.assign(temp, sizeof(Pack) + data.length());
    delete []temp;
}

bool Packet::unpack(string &data, int& packId, std::string &out) {
    if( data.length() < sizeof(Pack) ) return false;

    Pack pack;
    memset(&pack,0, sizeof(Pack));
    memcpy(&pack, data.data(), sizeof(Pack));
    if( data.length() < pack.length + sizeof(Pack) ) return false;

    out.assign(data.data() + sizeof(Pack), pack.length);
    data.erase(0, pack.length + sizeof(Pack));
    packId = pack.packId;
    return true;
}