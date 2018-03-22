#if __APPLE__

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include "socket.h"

using namespace std;

namespace net {
    Socket::Socket() {
        if ((_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("ERROR opening socket");
        }
    }

    Socket::Socket(int sockfd)
            : _sockfd(sockfd) {
        if (_sockfd < 0) {
            perror("ERROR opening socket");
        }
    }

    Socket::~Socket() {
        disconnect();
    }

    void Socket::listen(int port) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);
        if (::bind(_sockfd, (sockaddr *) &addr, sizeof(addr)) < 0) {
            perror("ERROR opening socket");
            return;
        }

        if (::listen(_sockfd, 10) < 0) {
            perror("ERROR opening socket");
            return;
        }

        int csockfd = -1;
        if ((csockfd = accept(_sockfd, (sockaddr *) &addr, (socklen_t *) &addr)) < 0) {
            perror("ERROR opening socket");
            return;
        }
    }

    bool Socket::connect(string hostname, int port) {
        if (_sockfd < 0) {
            perror("ERROR opening socket");
            return false;
        }

        _port = port;
        _hostname = hostname;

        int ret = 0;
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_len = sizeof(addr);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(_port);
        addr.sin_addr.s_addr = inet_addr(hostname.c_str());

        ret = ::connect(_sockfd, (sockaddr *) &addr, sizeof(addr));
        if (ret < 0) {
            char *msg = strerror(ret);
            cout << "[error]" << msg << endl;
            return false;
        }
        return true;
    }

    void Socket::disconnect() {
        if (_sockfd < 0) {
            return;
        }

        shutdown(_sockfd, SHUT_RDWR);
        _sockfd = -1;
    }

    void Socket::send(const void *data, int len) {
        if (_sockfd < 0) {
            return;
        }
        ::send(_sockfd, data, len, 0);
    }

    void Socket::receive() {
    }
}

#endif