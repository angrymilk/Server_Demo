#include "GameServer.h"
/*
void DemoServer::serialize_and_send(shared_ptr<std::string> message, int srcPlayer, int dst_player, int messgeType)
{
    Response res;
    res.set_srcplayerid(srcPlayer);
    res.set_message(*message);
    //res.set_message("sadfsafsaf");

    char data[COMMON_BUFFER_SIZE];
    MsgHead head;
    head.m_message_len = res.ByteSize() + MESSAGE_HEAD_SIZE;

    int codeLength = 0;
    head.encode(data, codeLength);
    res.SerializePartialToArray(data + codeLength, res.ByteSize());
    if (m_map_players.find(dst_player) == m_map_players.end())
    {
        printf("[DemoServer.cpp:%d][ERROR]:No uin in server uin:%d\n", __LINE__, dst_player);
        return;
    }
    int ret = 0;
    int fd = 0;
    vector<int> deletePlayer;
    for (unordered_map<int, PlayerInfo>::iterator iter = m_map_players.begin(); iter != m_map_players.end(); iter++)
    {
        fd = m_map_players[iter->first].fd;
        if (m_sockets_map.find(fd) == m_sockets_map.end())
        {
            printf("[DemoServer.cpp:%d][WARNING]:fd:[%d] is not in the map now,maybe is deleted\n", __LINE__, fd);
            deletePlayer.emplace_back(iter->first);
            continue;
        }
        ret = m_sockets_map[fd]->send_data(data, (size_t)head.m_message_len);
        if (ret < success)
        {
            printf("[DemoServer.cpp:%d][ERROR]:Send msg (id=%d) error ret=%d,errno:%d ,strerror:%s,fd = %d\n", __LINE__, messgeType, ret, errno, strerror(errno), fd);
        }
        if (ret > success)
        {
            printf("[DemoServer.cpp:%d][INFO]:Send msg (id=%d)  try multi ret=%d, errno:%d ,strerror:%s, fd = %d\n", __LINE__, messgeType, ret, errno, strerror(errno), fd);
        }
    }
    for (vector<int>::iterator iter = deletePlayer.begin(); iter != deletePlayer.end(); iter++)
        m_map_players.erase(*iter);
    printf("[DemoServer.cpp:%d][INFO]:Send Message msglen = %d\n", __LINE__, head.m_message_len);
}

int DemoServer::parsing_and_send(const char *pszInCode, const int iInCodeSize, int socketFd)
{
    if (!pszInCode || iInCodeSize <= 0)
    {
        return fail;
    }

    MsgHead stHead;
    if (success != stHead.decode(pszInCode, iInCodeSize))
    {
        printf("[DemoServer.cpp:%d][ERROR]:head decode error\n", __LINE__);
        return fail;
    }

    if (stHead.m_message_len != iInCodeSize)
    {
        printf("[DemoServer.cpp:%d][ERROR]:the package size decoded from service was not equal with received size.\n", __LINE__);
        return fail;
    }

    int bodySize = stHead.m_message_len - MESSAGE_HEAD_SIZE;

    Reqest req;
    req.ParseFromArray(pszInCode + MESSAGE_HEAD_SIZE, bodySize);
    if (m_map_players.find(req.srcplayerid()) == m_map_players.end())
    {
        m_map_players[req.srcplayerid()].fd = socketFd;
        m_map_players[req.srcplayerid()].player = make_shared<Player>(req.srcplayerid());
    }

    if (req.messagetype() == -1)
    {
        cout << "################Server Recieved Player:["
             << req.srcplayerid()
             << "]'s Message: ["
             << req.message()
             << "] And Send To Player:["
             << req.desplayerid() << "]\n";
    }
    else if (req.messagetype() == 1)
    {
        cout << "################Server Recieved Player:["
             << req.srcplayerid()
             << "]'s Message: ["
             << req.message()
             << "] And Send To All Players\n";
    }
    else
    {
        printf("[DemoServer.cpp:%d][ERROR]:Not Support Message Id:[%d] Now\n", __LINE__, req.messagetype());
        return fail;
    }
    std::shared_ptr<std::string> ptr = make_shared<std::string>(req.message());
    serialize_and_send(ptr, req.srcplayerid(), req.desplayerid(), req.messagetype());
    return success;
}

*/

GameServer::GameServer(std::string ip, int port)
{
    m_server.reset(new BaseServer(ip, port, std::bind(m_on_message, this, std::placeholders::_1)));
}

int GameServer::run()
{
    if (m_server->run())
        return -101;
    return 0;
}

int GameServer::m_on_message(TCPSocket &con)
{
    //将函数扔入计算线程中
    //thread.run(parase(con));
    get_one_code(con);
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
    int bodySize = datasize - MESSAGE_HEAD_SIZE;
    Reqest req;
    req.ParseFromArray(const_cast<char *>(data.c_str()) + MESSAGE_HEAD_SIZE, bodySize);
    printf("[GameServer][GameServer.cpp:%d][INFO]:get_information:[%s]\n", __LINE__, req.message());
    Response res;
    res.set_message(req.message());

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
}

void GameServer::serialize(TCPSocket &con, std::string &data, std::string &out)
{
    //序列化处理
}

void GameServer::parse(char *input, int &size)
{
    //反序列化处理
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