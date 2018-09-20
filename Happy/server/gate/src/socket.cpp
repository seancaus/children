//
// Created by Ziv on 2018/3/26.
//

#include <cstdlib>
#include <iostream>

#include "uv.h"
#include "socket.h"
#include "module/server/Packet.h"

using namespace std;

#define DEFAULT_BACKLOG 128

typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

typedef struct {
    uv_work_t req;
    uv_stream_t *client;
} work_req_t;

void new_connection(uv_stream_t* server, int status)
{
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }

    auto sock = (Socket*)server->data;

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    client->data = sock;
    if ( 0 == uv_accept(server, (uv_stream_t*) client) ) {
        sock->accept((uv_stream_t*) client);
    }
    else {
        uv_close((uv_handle_t*) client, [](uv_handle_t* handle) {
            free(handle);
        });
    }
}

Socket::Socket(shared_ptr<Packet> packet)
    :_packet(packet)
{
    if(nullptr == _packet) {
        _packet = make_shared<Packet>();
    }
}


Socket::~Socket() {
    uv_loop_close(_loop);
}

void Socket::listen(unsigned int port) {
    _loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(_loop, &server);
    server.data = this;

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", port, &addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    int r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, new_connection);

    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return;
    }
    uv_run(_loop, UV_RUN_DEFAULT);
}

void Socket::accept(uv_stream_t* client) {
    work_req_t work;
    work.req.data = this;
    work.client = client;

    uv_queue_work(_loop, (uv_work_t*)&work, [](uv_work_t* req){
        work_req_t* work = (work_req_t*)req;
        Socket* sock = (Socket*)work->req.data;
        sock->read(work->client);
    },
    [](uv_work_t* req, int status){

    });
}

void Socket::read(uv_stream_t* client) {
    uv_read_start(client, [](uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
        buf->base = (char*) malloc(suggested_size);
        buf->len = suggested_size;
    }, [](uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
        if (nread > 0) {
            Socket* sock = (Socket*)client->data;
            string str = "你说:";
            str.append(buf->base);
            sock->send(client,const_cast<char*>(str.data()),str.length());
        }

        if (nread < 0) {
            if (nread != UV_EOF)
                fprintf(stderr, "Read error %s\n", uv_err_name(nread));

                uv_close((uv_handle_t*) client, [](uv_handle_t* handle) {
                free(handle);
            });
        }
        free(buf->base);
    });
}

void Socket::send(uv_stream_t* client,char *data, unsigned int nlen) {
    write_req_t *req = (write_req_t*) malloc(sizeof(write_req_t));
    req->buf = uv_buf_init(data, nlen);
    uv_write((uv_write_t*) req, client, &req->buf, 1, [](uv_write_t *req, int status) {
        if (status) {
            fprintf(stderr, "Write error %s\n", uv_strerror(status));
        }
        write_req_t *wr = (write_req_t*) req;
        free(wr);
    });
}





