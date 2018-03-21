//
// Created by Ziv on 2018/3/20.
//

#ifndef MAHJONGSERVER_SOCKET_H
#define MAHJONGSERVER_SOCKET_H

struct event_base;

class Socket {
public:
    Socket();
    ~Socket();
    void listen(unsigned int port);

protected:
    struct event_base* _eventBase;
};


#endif //MAHJONGSERVER_SOCKET_H
