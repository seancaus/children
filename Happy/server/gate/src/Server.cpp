//
// Created by Ziv on 2018/3/28.
//

#include <iostream>
#include <uvw.hpp>

#include "Server.h"
#include "Packet.h"
#include "MessageManager.h"

using namespace uvw;
using namespace std;

Server::Server()
        : _loop(nullptr) {
    _packer = make_unique<Packet>();
    _msgManager = make_shared<MessageManager>();
}

Server::~Server() {
//    _loop->stop();
//    _loop->close();
}

void Server::start() {
    if (_loop) _loop->close();

    _loop = Loop::getDefault();

    auto server = _loop->resource<TcpHandle>();
    server->on<uvw::ErrorEvent>(std::bind(&Server::onError,this,placeholders::_1, placeholders::_2));
    server->on<ListenEvent>(std::bind(&Server::onConnect, this, placeholders::_1, placeholders::_2));
    server->bind("127.0.0.1", 9999);
    server->listen();

    _loop->run();
}

void Server::send(uvw::TcpHandle &client, int packId, std::string &data) {
    string msg;
    _packer->pack(packId, data, msg);
    client.write(const_cast<char*>(msg.data()), msg.length());
}

void Server::onConnect(const ListenEvent &event, TcpHandle &handle) {
    string data("");
    typedef std::function<void(const DataEvent &, TcpHandle &)> DataEventCallback;
    DataEventCallback dataEventCallback = std::bind(&Server::onRecv, this, placeholders::_1, placeholders::_2, data);

    shared_ptr<TcpHandle> client = handle.loop().resource<TcpHandle>();
    client->on<DataEvent>(dataEventCallback);
    client->on<ShutdownEvent>(std::bind(&Server::onShutdown,this,placeholders::_1, placeholders::_2));
    client->on<CloseEvent>(std::bind(&Server::onClose,this,placeholders::_1, placeholders::_2));

    handle.accept(*client);
    auto req = _loop->resource<WorkReq>([&client, &handle]() {
        client->read();
    });
    req->queue();
}

void Server::onRecv(const DataEvent &event, TcpHandle &handle, string &data) {
    data.append(event.data.get(), event.length);

    unsigned int packid;
    string msg;
    if( 0 == (packid = _packer->unpack(data, msg)) )return;

    _msgManager->dispatchMessage(packid, msg);

    send(handle,1,msg);
}

void Server::onShutdown(const ShutdownEvent &event, uvw::TcpHandle &client) {
    cout << "on Shutdown" <<  &client << endl;
//    client.close();
}

void Server::onClose(const CloseEvent &event, TcpHandle &client) {
//    [ptr = handle.shared_from_this()](const CloseEvent &, TcpHandle &) { ptr->close(); }
    cout << "on client close" << endl;
}

void Server::onError(const uvw::ErrorEvent &event, uvw::TcpHandle &handle) {
    cout << event.name()<<":"<< event.what() << endl;
}

const shared_ptr<MessageManager>& Server::getServiceManager() const {
    return _msgManager;
}