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
        delete m_msgHandle;
    }
    int run();
    int on_message(TCPSocket &con);
    void get_one_code(TCPSocket &con);
    void solve(TCPSocket &con, std::string &data, int datasize);
    void serialize(char *data, Player &temp);
    void parse(char *input, Player &player, int &size);
    void send(char *data, int size);
    void handle_move(Player &player);
    void handle_attack(Player &player);
    ThreadTask m_thread_task;

private:
    std::shared_ptr<BaseServer> m_server;
    std::unordered_map<int, PlayerInfo> m_map_players;
    MsgHandler<Player> *m_msgHandle = nullptr;
    std::vector<Player> m_player_vec;
};
#endif