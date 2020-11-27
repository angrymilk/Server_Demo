#include "GameServer.h"
#include <stdio.h>
#include <stdlib.h>
GameServer::GameServer(std::string ip, int port)
{
    m_redis_server.reset(new RedisServer("127.0.0.1", 6379));
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

void GameServer::regist(TCPSocket &con, std::string &data, int datasize)
{
    Reqest req;
    req.ParseFromArray(const_cast<char *>(data.c_str()) + MESSAGE_HEAD_SIZE, datasize);
    if (m_name_map.find(req.name()) == m_name_map.end())
    {
        m_name_map[req.name()] = rand();
        m_map_players[m_name_map[req.name()]].fd = con.get_fd();
        m_map_players[m_name_map[req.name()]].player = make_shared<Player>(new Player(m_name_map[req.name()]));
    }

    Response res;
    res.set_id = m_name_map[req.name()];
    res.set_message(req.message());

    char data_[COMMON_BUFFER_SIZE];
    MsgHead head;
    head.m_message_len = res.ByteSize() + MESSAGE_HEAD_SIZE;
    int temp = head.m_message_len;
    int codeLength = 0;
    head.encode(data_, codeLength);
    res.SerializePartialToArray(data_ + temp, res.ByteSize());
    con.send(std::bind(&GameServer::send, this, data_, temp));
}

void GameServer::solve_add(TCPSocket &con, std::string &data, int datasize)
{
    //基本逻辑处理->调用con的发送函数
    int bodySize = (datasize & ((1 << 20) - 1)) - MESSAGE_HEAD_SIZE;
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
        m_map_players[req.uid()].player->add(info, req.pos(), req.num(), req.dropfrom());
    }
    else
    {
        m_map_players[req.uid()].player->consume(req.uid(), req.eltemtype(), req.value(), req.dropfrom(), req.inuse());
    }
    //############################################  进行数据格式化方便进行redis的数据落地  ########################################################

    Redisplayerinfo tmp;
    tmp.set_hp(m_map_players[req.uid()].player->get_hp());
    tmp.set_attack(m_map_players[req.uid()].player->get_attack());
    tmp.set_id(req.uid());
    //存储目前正在使用的道具的信息
    for (unordered_map<int, std::shared_ptr<AbstractItem>>::iterator iter = m_map_players[req.uid()].player->m_in_use.begin(); iter != m_map_players[req.uid()].player->m_in_use.end(); iter++)
    {
        Attributeitempro *temp = tmp.add_Attributeitempro();

        std::shared_ptr<AbstractItem> ptr = m_map_players[req.uid()].player->m_in_use[iter->first];
        temp->set_amount(ptr->get_amount());
        temp->set_id(ptr->get_uid());
        temp->set_mtype(ptr->get_eltem_type());
        temp->add_int32(ptr->get_attribute(EltemModuleType::eltem_Module_Base, EltemAttributeType::eltem_Attribute_Attack));
        temp->add_int32(ptr->get_attribute(EltemModuleType::eltem_Module_Base, EltemAttributeType::eltem_Attribute_HP));
        temp->add_int32(ptr->get_attribute(EltemModuleType::eltem_Module_Power, EltemAttributeType::eltem_Attribute_Attack));
        temp->add_int32(ptr->get_attribute(EltemModuleType::eltem_Module_Power, EltemAttributeType::eltem_Attribute_HP));
        temp->add_int32(ptr->get_attribute(EltemModuleType::eltem_Module_Insert, EltemAttributeType::eltem_Attribute_Attack));
        temp->add_int32(ptr->get_attribute(EltemModuleType::eltem_Module_Insert, EltemAttributeType::eltem_Attribute_HP));
    }
    //存储背包相关的信息
    std::shared_ptr<Package> ptr = m_map_players[req.uid()].player->get_package();
    std::vector<std::vector<std::shared_ptr<AbstractItem>>> vec = ptr->get_vec();
    Packagepro *packagein = tmp.add_Packagepro();
    for (int i = 0; i > vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            Attributeitempro *temp = packagein->add_Attributeitempro();

            temp->set_amount(vec[i][j]->get_amount());
            temp->set_id(vec[i][j]->get_uid());
            temp->set_mtype(vec[i][j]->get_eltem_type());
            temp->add_int32(vec[i][j]->get_attribute(EltemModuleType::eltem_Module_Base, EltemAttributeType::eltem_Attribute_Attack));
            temp->add_int32(vec[i][j]->get_attribute(EltemModuleType::eltem_Module_Base, EltemAttributeType::eltem_Attribute_HP));
            temp->add_int32(vec[i][j]->get_attribute(EltemModuleType::eltem_Module_Power, EltemAttributeType::eltem_Attribute_Attack));
            temp->add_int32(vec[i][j]->get_attribute(EltemModuleType::eltem_Module_Power, EltemAttributeType::eltem_Attribute_HP));
            temp->add_int32(vec[i][j]->get_attribute(EltemModuleType::eltem_Module_Insert, EltemAttributeType::eltem_Attribute_Attack));
            temp->add_int32(vec[i][j]->get_attribute(EltemModuleType::eltem_Module_Insert, EltemAttributeType::eltem_Attribute_HP));
        }
    }

    char key[4];
    char out[1001];
    m_redis_server->Connect();
    itoa(tmp.id(), key, 4);
    tmp.SerializePartialToArray(out, tmp.ByteSize());
    m_redis_server->SetByBit(key, out, tmp.ByteSize());
    //############################################################  结束数据格式化  ##################################################################
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

    {
    }
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