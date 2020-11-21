#include "GameServer.h"

GameServer::GameServer(std::string ip, int port)
{
    m_player_vec.reserve(10024);
    m_server.reset(new BaseServer(ip, port));
    m_server->set_read_callback(std::bind(&GameServer::on_message, this, std::placeholders::_1));
    m_thread_task.Start();
    m_msgHandle = new MsgHandler<Player>();
}

int GameServer::run()
{
    if (m_server->run())
        return -101;
    return 0;
}

int GameServer::on_message(TCPSocket &con)
{
    //将函数扔入计算线程中
    m_thread_task.submit(std::bind(&GameServer::get_one_code, this, con));
}

void GameServer::get_one_code(TCPSocket &con)
{
    int ret = 0;
    while (1)
    {
        size_t data_size = MAX_SS_PACKAGE_SIZE;
        std::string m_sRvMsgBuf;
        m_sRvMsgBuf.reserve(MAX_SS_PACKAGE_SIZE);
        ret = con.m_buffer->get_one_code(const_cast<char *>(m_sRvMsgBuf.c_str()), data_size);
        if (ret > 0)
        {
            solve(con, m_sRvMsgBuf, data_size);
            continue;
        }
        else if (ret < 0)
        {
            printf("[GameServer][GameServer.cpp:%d][ERROR]:get_one_code failed. errorCode:%d\n", __LINE__, ret);
        }
        break;
    }
}

void GameServer::solve(TCPSocket &con, std::string &data, int datasize)
{
    //基本逻辑处理->调用con的发送函数
    Player temp;
    parse(const_cast<char *>(data.c_str()), temp, datasize);
    handle_move(temp);
    char data_[COMMON_BUFFER_SIZE];
    serialize(data_, temp);
    vector<int> deletePlayer;
    for (unordered_map<int, PlayerInfo>::iterator iter = m_map_players.begin(); iter != m_map_players.end(); iter++)
    {
        int fd = m_map_players[iter->first].fd;
        if (m_server->m_sockets_map.find(fd) == m_server->m_sockets_map.end())
        {
            printf("[GameServer][GameServer.cpp:%d][WARNING]:fd:[%d] is not in the map now,maybe is deleted\n", __LINE__, fd);
            deletePlayer.emplace_back(iter->first);
            continue;
        }
    }
    for (vector<int>::iterator iter = deletePlayer.begin(); iter != deletePlayer.end(); iter++)
        m_map_players.erase(*iter);
    con.send(std::bind(&GameServer::send, this, data_, datasize));
}

void GameServer::serialize(char *data, Player &temp)
{
    //序列化处理
    MoveRsp res;
    res.set_name(temp.m_name);
    res.set_dirx(temp.dirx);
    res.set_diry(temp.diry);
    res.set_dirz(temp.dirz);
    res.set_trgx(temp.trgx);
    res.set_trgy(temp.trgy);
    res.set_trgz(temp.trgz);
    res.set_speed(temp.speed);
    res.set_time(temp.time);
    res.set_hp(temp.hp);
    res.set_hs(temp.hs);
    res.set_hs(temp.attack_id);
    MsgHead head;
    head.m_message_len = res.ByteSize() + MESSAGE_HEAD_SIZE;
    int codeLength = 0;
    head.encode(data, codeLength);
    res.SerializePartialToArray(data + codeLength, res.ByteSize());
}

void GameServer::parse(char *input, Player &player, int &size)
{
    //反序列化处理
    MoveReq req;
    req.ParseFromArray(input + MESSAGE_HEAD_SIZE, size - MESSAGE_HEAD_SIZE);
    player.m_name = req.name();
    player.dirx = req.dirx();
    player.diry = req.diry();
    player.dirz = req.dirz();
    player.trgx = req.trgx();
    player.trgy = req.trgy();
    player.trgz = req.trgz();
    player.speed = req.speed();
    player.time = req.time();
    player.hp = req.hp();
    player.hs = req.hs();
    player.attack_id = req.attack_id();
}

void GameServer::send(char *data, int size)
{
    int ret = 0;
    for (unordered_map<int, PlayerInfo>::iterator iter = m_map_players.begin(); iter != m_map_players.end(); iter++)
    {
        int fd = m_map_players[iter->first].fd;
        ret = m_server->m_sockets_map[fd]->send_data(data, size);
        if (ret < success)
        {
            printf("[GameServer][GameServer.cpp:%d][ERROR]:Send error ret=%d,errno:%d ,strerror:%s,fd = %d\n", __LINE__, ret, errno, strerror(errno), fd);
        }
        if (ret > success)
        {
            printf("[GameServer][GameServer.cpp:%d][INFO]:Send try multi ret=%d, errno:%d ,strerror:%s, fd = %d\n", __LINE__, ret, errno, strerror(errno), fd);
        }
    }
}

void GameServer::handle_move(Player &player)
{
    int uid = player.get_id();
    Player player_ = m_player_vec[uid];
    int delta_time = player.time - player_.time;
    float move_rate = delta_time * player_.speed / sqrt((player.trgx - player_.trgx) * (player.trgx - player_.trgx) + (player.trgz - player_.trgz) * (player.trgz - player_.trgz));
    int x = player.trgx + move_rate * player.dirx;
    int z = player.trgz + move_rate * player.dirz;
    //int y = player.trgy + move_rate * player.diry;
    if (10 < (x - player_.trgx) * (x - player_.trgx) + (z - player_.trgz) * (z - player_.trgz))
    {
        //如果差距太大做拉回的操作
        player.m_is_cheat = true;
        player.dirx = player_.dirx;
        player.diry = player.diry;
        player.dirz = player.dirz;
        player.trgx = player.trgx;
        player.trgy = player.trgy;
        player.trgz = player.trgz;
        player.speed = player.speed;
        player.time = player.time;
        player.hp = player.hp;
        player.hs = player.hs;
        player.attack_id = player.attack_id;
    }
    else
        m_player_vec[uid] = player;
}

//TODO
void GameServer::handle_attack(Player &player)
{
    int id = player.attack_id;
}