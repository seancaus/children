//
// Created by Ziv on 2018/3/28.
//

#include <iostream>
#include <fstream>
#include <uvw.hpp>
#include <cassert>

#include "module/server/Server.h"
#include "module/server/Packet.h"
#include "module/server/MessageManager.h"
#include "utils/uuid.h"

using namespace uvw;
using namespace std;

Server::Server()
        : _loop(nullptr)
        ,_packer(nullptr)
        ,_msgManager(nullptr)
{
}

Server::~Server()
{
    if(_loop)
    {
        _loop->stop();
        _loop->close();
    }
}

//-------------------------------------------------------------------------------------
void Server::start(string ip, unsigned int port, shared_ptr<Packet> packer, shared_ptr<MessageManager> msgManager)
{
    this->_packer = packer;
    this->_msgManager = msgManager;

    if(nullptr == _packer || nullptr == _msgManager)
    {
        cout << "_packer is nullptr or _msgManager is nullptr" << endl;
        return;
    }

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

    _clients.insert(make_pair(uuid, client));

    auto req = _loop->resource<WorkReq>([&client, &handle]() {
        client->read();
    });
    req->queue();

    string s = "1";
    authClient(uuid,s);
    send(s,1,s);
}

void Server::onRecv(const DataEvent &event, TcpHandle &client, string &data)
{
    data.append(event.data.get(), event.length);

    string msg;
    int packId;
    if( !_packer->unpack(data, packId, msg)) return;

    ofstream of("s.txt",std::ios::binary);
    of.write((msg).c_str(),(msg).length());
    shared_ptr<string> uuid = client.data<string>();
    _msgManager->dispatchMessage(packId, *uuid.get(), msg);
}

//-------------------------------------------------------------------------------------
void Server::authClient(std::string &uuid, std::string &uid)
{
    auto iter = _clients.find(uuid);
    if( _clients.end() == iter )
    {
        cout << "don't have client form uuid: " << uuid << endl;
        return;
    }

    auto curClient = _authClients[uid];
    if(curClient)
    {
        _authClients.erase(uid);
        curClient->shutdown();
    }

    iter->second->data(make_shared<string>(uid));
    _authClients[uid] = iter->second;
    _clients.erase(iter);
}

//-------------------------------------------------------------------------------------
void Server::send(std::string &uid, int packId, std::string &data)
{
    auto client = _authClients[uid];
    if(not client){
        cout << "don't have uuid: " << uid << endl;
        return;
    }
    send(client, packId, data);
}

void Server::send(shared_ptr<TcpHandle> client, int packId, string &data)
{
    string msg;
    _packer->pack(packId, data, msg);
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