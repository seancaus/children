//
// Created by Ziv on 2018/3/28.
//

#ifndef MAHJONGSERVER_SERVER_H
#define MAHJONGSERVER_SERVER_H

#include <map>
#include <memory>
#include <string>
#include <functional>

namespace uvw{
    class Loop;
    class TcpHandle;

    struct ShutdownEvent;
    struct CloseEvent;
    struct ErrorEvent;
    struct DataEvent;
    struct ListenEvent;
}

class Packet;
class MessageManager;

class Server {

public:
    Server();
    virtual ~Server();

    void start(std::string ip = "127.0.0.1", unsigned int port = 9999, std::shared_ptr<Packet> packer = nullptr, std::shared_ptr<MessageManager> msgManager = nullptr);
    void onConnect(const uvw::ListenEvent &, uvw::TcpHandle &handle);
    void onRecv(const uvw::DataEvent &event, uvw::TcpHandle &handle,std::string &data);

    void authClient(std::string &uuid,std::string &uid);

    void send(std::string &uid, int packId, std::string &data);
    void send(std::shared_ptr<uvw::TcpHandle> handle, int packId, std::string &data);

    void onError(const uvw::ErrorEvent &, uvw::TcpHandle &);
    void onShutdown(const uvw::ShutdownEvent &, uvw::TcpHandle &client);
    void onClose(const uvw::CloseEvent &event, uvw::TcpHandle &handle);

protected:

    std::shared_ptr<uvw::Loop>          _loop;
    std::shared_ptr<Packet>             _packer;
    std::shared_ptr<MessageManager>     _msgManager;

    std::map<std::string, std::shared_ptr<uvw::TcpHandle>> _clients;
    std::map<std::string, std::shared_ptr<uvw::TcpHandle>> _authClients;
};


#endif //MAHJONGSERVER_SERVER_H
