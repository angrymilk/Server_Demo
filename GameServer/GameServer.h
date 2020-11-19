#ifndef DEMO_SERVER_H
#define DEMO_SERVER_H
#include "../Common/BaseServer.h"
#include "../Common/MesHead.h"
#include "Player.h"
#include "../Common/ThreadPool.h"
#include "../Common/TCPSocket.h"
struct PlayerInfo
{
    int fd;
    shared_ptr<Player> player;
};

class GameServer
{
public:
    GameServer(std::string ip, int port);
    int run();
    int on_message(TCPSocket &con);
    void get_one_code(TCPSocket &con);
    void solve(TCPSocket &con, std::string &data, int datasize);
    void serialize(TCPSocket &con, std::string &data, std::string &out);
    void parse(char *input, int &size);
    void send(char *data, int size);

private:
    std::shared_ptr<BaseServer> m_server;
    std::unordered_map<int, PlayerInfo> m_map_players;
    //ThreadPool m_thread_pool;
};

#endif