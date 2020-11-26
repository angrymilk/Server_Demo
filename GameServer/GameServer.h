#ifndef DEMO_SERVER_H
#define DEMO_SERVER_H
#include "../Common/BaseServer.h"
#include "../Common/MesHead.h"
#include "Player.h"
#include "../Common/TCPSocket.h"
#include "../Common/ThreadTask.h"
struct PlayerInfo
{
    int fd;
    shared_ptr<Player> player;
};

class GameServer
{
public:
    GameServer(std::string ip, int port);
    ~GameServer()
    {
        m_thread_task.stop();
    }
    int run();
    int on_message(TCPSocket &con);
    void get_one_code(TCPSocket &con);
    void solve(TCPSocket &con, std::string &data, int datasize);
    void serialize(TCPSocket &con, std::string &data, std::string &out, int type);
    void parse(char *input, int &size, int type);
    void send(char *data, int size);
    void solve_data(TCPSocket &con, std::string &data, int datasize);
    //场景物品初始化函数
    void scen_init();
    ThreadTask m_thread_task;

private:
    std::shared_ptr<BaseServer> m_server;
    std::unordered_map<int, PlayerInfo> m_map_players;
};
#endif