#ifndef DEMO_SERVER_H
#define DEMO_SERVER_H
#include "../Common/BaseServer.h"
#include "../Common/MesHead.h"
#include "Player.h"

struct PlayerInfo
{
    int fd;
    shared_ptr<Player> player;
};

//typedef void (*ServerSendCallBack) (int uin, int cmd_id, google::protobuf::Message &msg);
class DemoServer : public BaseServer
{
public:
    DemoServer(std::string ip, int port) : BaseServer(ip, port)
    {
    }

    int run();
    //void serialize_and_send(shared_ptr<std::string> message, int src_player, int dst_player, int messge_type);

private:
    //int parsing_and_send(const char *pszInCode, const int iInCodeSize, int socketfd);
    std::unordered_map<int, PlayerInfo> m_map_players;
};

#endif