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
    GameServer(std::string ip, int port, ReadFunctor read_func);
    int run();
    int m_on_message(const TCPSocket &con);
    void parase(const TCPSocket &con);
    void send(const TCPSocket &con, std::string &data);
    void solve(const TCPSocket &con, std::string &data);

private:
    std::shared_ptr<BaseServer> m_server;
    std::unordered_map<int, PlayerInfo> m_map_players;
    //ThreadPool m_thread_pool;
};

#endif