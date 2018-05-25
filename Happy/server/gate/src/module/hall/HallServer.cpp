//
// Created by Ziv on 2018/4/26.
//

#include <Application.h>
#include <handle/Handler.h>
#include "module/hall/HallServer.h"
#include "module/hall/hall_generated.h"

using namespace share::hall;
using namespace flatbuffers;
using namespace std;

HallServer::HallServer() {

}

void HallServer::handleMessage(std::string& uid, std::string& msg) {
    const Message* object = GetMessage(msg.data());
    switch(object->object_type()){
        case Any_LoginRequest:{
            this->onLogin(uid,object);
            break;
        }
        default:
        {
            break;
        }
    }
}


void HallServer::onLogin(std::string& uuid,const share::hall::Message *message) {
    auto msg = message->object_as<LoginRequest>();

    Offset<String> ca;
    Offset<String> uid;
    Offset<String> nickName;

    string userid;
    flatbuffers::FlatBufferBuilder builder;
    if(nullptr == msg->ca())
    {
        userid = "1";
        ca = builder.CreateString(userid);
        uid = builder.CreateString(userid);
        nickName = builder.CreateString("同学1");
    }else{
        userid = msg->ca()->str();
        ca = builder.CreateString(userid);
        uid = builder.CreateString(userid);

        string nname("");
        nname.append("同学").append(userid);
        nickName = builder.CreateString(nname);
    }

    UserBuilder player(builder);
    player.add_ca(ca);
    player.add_uid(uid);
    player.add_nickName(nickName);

    auto reply = CreateMessage(builder,Any_LoginReply,CreateLoginReply(builder, player.Finish()).Union());
    builder.Finish(reply);

    Application::getInstance().authPlayer(userid, uuid);
    string replyMsg(reinterpret_cast<const char*>(builder.GetBufferPointer()),builder.GetSize());
    Application::getInstance().send(userid,Handler_Hall,replyMsg);
    Application::getInstance().send(userid,Handler_Room,replyMsg);
}



