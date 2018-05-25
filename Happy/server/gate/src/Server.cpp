//
// Created by Ziv on 2018/3/28.
//

#include <iostream>
#include <fstream>
#include <uvw.hpp>
#include <cassert>

#include "Server.h"
#include "Packet.h"
#include "utils/uuid.h"

using namespace uvw;
using namespace std;

Server::Server()
        : _loop(nullptr)
        , _receiveHandler(nullptr)
{
    _packer = make_unique<Packet>();
}

Server::~Server()
{
    _loop->stop();
    _loop->close();
}

//-------------------------------------------------------------------------------------
void Server::start(string ip, unsigned int port)
{
    if (_loop) _loop->close();

    _loop = Loop::getDefault();

    auto server = _loop->resource<TcpHandle>();
    server->on<ErrorEvent>(bind(&Server::onError,this,placeholders::_1, placeholders::_2));
    server->on<ListenEvent>(bind(&Server::onConnect, this, placeholders::_1, placeholders::_2));
    server->bind(ip, port);
    server->listen();

    _loop->run();
}

void Server::onConnect(const ListenEvent &event, TcpHandle &handle)
{
    string data("");
    typedef function<void(const DataEvent &, TcpHandle &)> DataEventCallback;
    DataEventCallback dataEventCallback = bind(&Server::onRecv, this, placeholders::_1, placeholders::_2, data);

    auto uuid = uuid::genUUID();
    auto client = handle.loop().resource<TcpHandle>();
    client->data(make_shared<string>(uuid));
    client->on<DataEvent>(dataEventCallback);
    client->on<ShutdownEvent>(bind(&Server::onShutdown,this,placeholders::_1, placeholders::_2));
    client->on<CloseEvent>(bind(&Server::onClose,this,placeholders::_1, placeholders::_2));

    handle.accept(*client);

    _tempClients.insert(make_pair(uuid, client));

    auto req = _loop->resource<WorkReq>([&client, &handle]() {
        client->read();
    });
    req->queue();
}

void Server::onRecv(const DataEvent &event, TcpHandle &client, string &data)
{
    data.append(event.data.get(), event.length);

    string msg;
    size_t msgId;
    if( -1 == (msgId = _packer->unpack(data, msg)) )return;

    if( !_receiveHandler ){
        cout << "_receiveHandler is nullptr" << endl;
        return;
    }

    ofstream of("s.txt",std::ios::binary);
    of.write((msg).c_str(),(msg).length());
    shared_ptr<string> uuid = client.data<string>();
    _receiveHandler(msgId, *uuid.get(), msg);
}

//-------------------------------------------------------------------------------------
void Server::authClient(std::string &uuid, std::string &uid)
{
    auto authIter = _authClients.find(uid);
    if(authIter != _authClients.end())
    {
        _authClients.erase(authIter);
        authIter->second->shutdown();
    }

    auto iter = _tempClients.find(uuid);
    if(iter == _tempClients.end())
    {
        cout << "don't have client form uuid: " << uuid << endl;
        return;
    }

    _tempClients.erase(iter);

    auto client = iter->second;
    client->data(make_shared<string>(uid));
    _authClients.insert(make_pair(uid, client));
}

//-------------------------------------------------------------------------------------
void Server::send(std::string &uuid,unsigned int msgId, std::string &data)
{
    assert(msgId > 0);

    if(_authClients.end() == _authClients.find(uuid)){
        cout << "don't have uuid: " << uuid << endl;
        return;
    }
    auto client = _authClients[uuid];
    send(client, msgId, data);
}

void Server::send(shared_ptr<TcpHandle> client, unsigned int msgId, string &data)
{
    string msg;
    _packer->pack(msgId, data, msg);
    client->write(const_cast<char*>(msg.data()), msg.length());
}
//-------------------------------------------------------------------------------------

void Server::onShutdown(const ShutdownEvent &event, TcpHandle &client)
{
    cout << "on Shutdown" <<  &client << endl;
//    client.close();
}

void Server::onClose(const CloseEvent &event, TcpHandle &client)
{
//    [ptr = handle.shared_from_this()](const CloseEvent &, TcpHandle &) { ptr->close(); }
    cout << "on client close" << endl;
}

void Server::onError(const ErrorEvent &event, TcpHandle &handle)
{
    cout << event.name()<<":"<< event.what() << endl;
}
//-------------------------------------------------------------------------------------

void Server::set_handler(const ReceiveHandler &_handler)
{
    _receiveHandler = _handler;
}