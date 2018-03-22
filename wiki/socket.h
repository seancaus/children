#ifndef __NET_SOCKET_H__
#define __NET_SOCKET_H__

#include <string>

using namespace std;

namespace net {

    class PacketHead{
        unsigned long dataLen;
        char *data;
    };

    class Socket {

    public:
        Socket();

        Socket(int sockfd);

        ~Socket();

        void listen(int port);

        void startAccept();

        bool connect(string hostname, int port);

        void disconnect();

        void send(const void *data, int len);

        void recv();

    protected:

    protected:
        string _hostname;
        int _port;

        int _sockfd;
    };
}

#endif