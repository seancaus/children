//
// Created by Ziv on 2018/3/28.
//

#ifndef MAHJONGSERVER_SERVER_H
#define MAHJONGSERVER_SERVER_H

#include <map>
#include <memory>

using namespace std;

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

    void start();
    void send(uvw::TcpHandle &handle, int packId, std::string &data);

    void onConnect(const uvw::ListenEvent &, uvw::TcpHandle &handle);
    void onRecv(const uvw::DataEvent &event, uvw::TcpHandle &handle,string &data);
    void onError(const uvw::ErrorEvent &, uvw::TcpHandle &);
    void onShutdown(const uvw::ShutdownEvent &, uvw::TcpHandle &client);
    void onClose(const uvw::CloseEvent &event, uvw::TcpHandle &handle);


    const shared_ptr<MessageManager> &getServiceManager() const;

protected:

    shared_ptr<uvw::Loop>   _loop;
    unique_ptr<Packet>      _packer;

    shared_ptr<MessageManager> _msgManager;
};


#endif //MAHJONGSERVER_SERVER_H
