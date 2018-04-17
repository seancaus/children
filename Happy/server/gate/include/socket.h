//
// Created by Ziv on 2018/3/20.
//

#ifndef MAHJONGSERVER_SOCKET_H
#define MAHJONGSERVER_SOCKET_H

#include <memory>

using namespace std;

class Packet;
typedef struct uv_loop_s uv_loop_t;
typedef struct uv_stream_s uv_stream_t;

class Socket {
public:
    Socket(shared_ptr<Packet> packet = nullptr);
    ~Socket();
    void listen(unsigned int port);
    void accept(uv_stream_t* client);

    void read(uv_stream_t* client);
    void send(uv_stream_t* client, char* data, unsigned int nlen);

protected:
    uv_loop_t *         _loop;
    shared_ptr<Packet>  _packet;
};


#endif //MAHJONGSERVER_SOCKET_H
