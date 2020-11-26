#include "GameServer.h"
GameServer::GameServer(std::string ip, int port)
{
    m_server.reset(new BaseServer(ip, port));
    m_server->set_read_callback(std::bind(&GameServer::on_message, this, std::placeholders::_1));
    m_thread_task.Start();
    m_map_players[0].fd = -1; //场景代表
    m_map_players[0].player->set_uin(0);
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
            if (((data_size & ((1 << 20) & (1 << 21))) >> 20) == 1)
                solve_add(con, m_sRvMsgBuf, data_size);
            else if (((data_size & ((1 << 20) & (1 << 21))) >> 20) == 2)
                solve_query(con, m_sRvMsgBuf, data_size);
            else if (((data_size & ((1 << 20) & (1 << 21))) >> 20) == 0)
                regist(con, m_sRvMsgBuf, data_size);
            continue;
        }
        else if (ret < 0)
        {
            printf("[GameServer][GameServer.cpp:%d][ERROR]:get_one_code failed. errorCode:%d\n", __LINE__, ret);
        }
        break;
    }
}

void GameServer::solve_add(TCPSocket &con, std::string &data, int datasize)
{
    //基本逻辑处理->调用con的发送函数
    int bodySize = (datasize & ((1 << 20) - 1)) - MESSAGE_HEAD_SIZE;
    /*
    int bodySize = (datasize & ((1 << 20) - 1)) - MESSAGE_HEAD_SIZE;
    int proto_type = (datasize & ((1 << 20) & (1 << 21))) >> 20;
    printf("[GameServer][GameServer.cpp:%d][INFO]:proto_type = [%d]   message_len = [%d]\n", __LINE__, proto_type, bodySize);
    string tmp;
    serialize(con, data, tmp, proto_type);
    Reqest req;
    req.ParseFromArray(const_cast<char *>(data.c_str()) + MESSAGE_HEAD_SIZE, bodySize);
    printf("[GameServer][GameServer.cpp:%d][INFO]:get_information:", __LINE__);
    std::cout << req.message() << "\n";
    int playerId = req.srcplayerid();
    if (m_map_players.find(playerId) == m_map_players.end())
    {
        m_map_players[playerId].fd = con.get_fd();
    }

    Response res;
    res.set_message(req.message());
    res.set_srcplayerid(playerId);

    char data_[COMMON_BUFFER_SIZE];
    MsgHead head;
    head.m_message_len = res.ByteSize() + MESSAGE_HEAD_SIZE;
    int codeLength = 0;
    head.encode(data_, codeLength);
    res.SerializePartialToArray(data_ + codeLength, res.ByteSize());

    vector<int> deletePlayer;
    for (unordered_map<int, PlayerInfo>::iterator iter = m_map_players.begin(); iter != m_map_players.end(); iter++)
    {
        int fd = m_map_players[iter->first].fd;
        if (fd == -1)
            continue;
        if (m_server->m_sockets_map.find(fd) == m_server->m_sockets_map.end())
        {
            printf("[GameServer][GameServer.cpp:%d][WARNING]:fd:[%d] is not in the map now,maybe is deleted\n", __LINE__, fd);
            deletePlayer.emplace_back(iter->first);
            continue;
        }
    }
    for (vector<int>::iterator iter = deletePlayer.begin(); iter != deletePlayer.end(); iter++)
        m_map_players.erase(*iter);
    //ret = m_sockets_map[fd]->send_data(data, (size_t)head.m_message_len);
    con.send(std::bind(&GameServer::send, this, data_, head.m_message_len));
    //serialize();
    */
    Addreq req;
    req.ParseFromArray(const_cast<char *>(data.c_str()) + MESSAGE_HEAD_SIZE, bodySize);
    //printf("[GameServer][GameServer.cpp:%d][INFO]:UserId = [%d]   message_len = [%d]", __LINE__);
    if (req.value() > 0)
    {
        if (m_map_players.find(req.uid()) == m_map_players.end())
        {
            printf("[GameServer][GameServer.cpp:%d][ERROR]:No Such Player = [%d]\n", __LINE__, req.uid());
            return;
        }
        ItemInfo info;
        info.id = req.id();
        info.value = req.value();
        info.mtype = req.eltemtype();
        m_map_players[req.uid()].palyer->add(info, req.pos(), req.num(), req.dropfrom());
    }
    else
    {
        m_map_players[req.uid()].palyer->consume(req.uid(), req.eltemtype(), req.value(), req.dropfrom(), req.inuse());
    }

    Addres res;
    res.set_ack(1);

    char data_[COMMON_BUFFER_SIZE];
    MsgHead head;
    head.m_message_len = res.ByteSize() + MESSAGE_HEAD_SIZE;
    int temp = head.m_message_len;
    head.m_message_len = (head.m_message_len | (1 << 20));
    int codeLength = 0;
    head.encode(data_, codeLength);
    res.SerializePartialToArray(data_ + temp, res.ByteSize());
    con.send(std::bind(&GameServer::send, this, data_, temp));
}

void GameServer::solve_query(TCPSocket &con, std::string &data, int datasize)
{
    int bodySize = (datasize & ((1 << 20) - 1)) - MESSAGE_HEAD_SIZE;
    Packagereq req;
    Packageres res;
    req.ParseFromArray(const_cast<char *>(data.c_str()) + MESSAGE_HEAD_SIZE, bodySize);
    res.set_num(m_map_players[req.uid()].player->get_num(req.id()));

    char data_[COMMON_BUFFER_SIZE];
    MsgHead head;
    head.m_message_len = res.ByteSize() + MESSAGE_HEAD_SIZE;
    int temp = head.m_message_len;
    head.m_message_len = (head.m_message_len | (1 << 21));
    int codeLength = 0;
    head.encode(data_, codeLength);
    res.SerializePartialToArray(data_ + temp, res.ByteSize());
    con.send(std::bind(&GameServer::send, this, data_, temp));
}

void GameServer::serialize(TCPSocket &con, std::string &data, std::string &out, int type)
{
    //序列化处理
}

void GameServer::parse(char *input, int &size, int type)
{
    //反序列化处理
}

void GameServer::send(char *data, int size)
{
    int ret = 0;
    for (unordered_map<int, PlayerInfo>::iterator iter = m_map_players.begin(); iter != m_map_players.end(); iter++)
    {
        int fd = m_map_players[iter->first].fd;
        if (fd == -1)
            continue;
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