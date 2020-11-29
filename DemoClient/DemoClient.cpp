#include "DemoClient.h"
#include <thread>

DemoClient::DemoClient(ClientInfo tmp, ServerInfo ser) : m_clientinfo(tmp), m_serverinfo(ser)
{
    printf("Demo Client Is Starting Now !!!!!!!!!\n");
}

int DemoClient::working()
{
    int ret = 0;
    m_client_conn_socket = make_shared<TCPSocket>();
    ret = m_client_conn_socket->open_as_client(const_cast<char *>(m_clientinfo.ip.c_str()), m_clientinfo.port, m_clientinfo.bufferlen);
    if (ret)
        return ret;

    int tmpIp;
    ret = ip_string_to_addr(const_cast<char *>(m_serverinfo.ip.c_str()), tmpIp);
    if (ret)
        return ret;

    ret = m_client_conn_socket->connect_to(tmpIp, m_serverinfo.port, true, 100000000);
    if (ret)
        return ret;
    cout << "CLient FD\n";

    if (m_epoll.epoll_init(MAX_SOCKET_COUNT) < 0)
    {
        printf("epoll_init failed\n");
        return fail;
    }

    if (m_epoll.epoll_add(m_client_conn_socket->get_fd()) < 0)
    {
        printf("m_epoll.epoll_add fd:%d failed\n", m_client_conn_socket->get_fd());
        return fail;
    }

    if ((ret = m_epoll.epoll_add(STDIN_FILENO)) < 0)
    {
        printf("m_epoll.epoll_add fd:%d failed ret = %d  errno=%d\n", STDIN_FILENO, ret, errno);
        return fail;
    }

    m_client_read_socket.reset(new TCPSocket(STDIN_FILENO));

    cout << "Begin To Run Epoll...................\n";
    for (;;)
    {
        int timeout = -1;
        int fd_count = m_epoll.epoll_wait(timeout);
        cout << "Epoll Wait Ended................\n";

        for (int i = 0; i < fd_count; i++)
        {
            cout << "Epoll Has Happended\n";
            struct epoll_event *pstEvent = m_epoll.get_event(i);
            int socketfd = pstEvent->data.fd;
            if (socketfd == m_client_read_socket->get_fd())
            {
                handle_input_and_send();
            }
            else if (socketfd == m_client_conn_socket->get_fd())
            {
                int ret = m_client_conn_socket->process_data(std::bind(&DemoClient::process_code, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                if (fail == ret)
                {
                    printf("socket process_data failed fd:%d\n", m_client_conn_socket->get_fd());
                    return ret;
                }
            }
            else
            {
                printf("error fd_type\n");
                return -1;
                break;
            }
        }
    }
    return 0;
}

void DemoClient::handle_input_and_send()
{
    char buffer[COMMON_BUFFER_SIZE], data[MAX_SS_PACKAGE_SIZE];
    MsgHead head;
    int len = 0;
    printf("#####################  请描述你的操作: 1:修改人物的物品  2:查询人物拥有的物品 0:注册人物的信息   #######################\n");
    int ret = read(STDIN_FILENO, buffer, sizeof(buffer));
    if (atoi(buffer) == 1)
    {
        /*
        Addreq req;
        printf("#####################  请输入你的操作: 物品id           #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        req.set_id(atoi(buffer));
        printf("#####################  请输入你的操作: 物品类型         #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        req.set_eltemtype(atoi(buffer));
        printf("#####################  请输入你的操作: 修改的物品数量    #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        req.set_value(atoi(buffer));
        printf("#####################  请输入你的操作: 修改的玩家的id    #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        req.set_uid(atoi(buffer));
        printf("#####################  请输入你的操作: 是否花费金钱交易  #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (ret == 1)
            req.set_usemoney(true);
        else
            req.set_usemoney(false);
        printf("#####################  请输入你的操作: 道具放在背包的位置  #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        req.set_pos(atoi(buffer));
        printf("#####################  请输入你的操作: 道具从背包扔掉/放到使用背包中  #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (ret == 1)
            req.set_inuse(true);
        else
            req.set_inuse(false);
        printf("#####################  请输入你的操作: 道具从背包/使用背包列表扔掉  #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (ret == 1)
            req.set_dropfrom(true);
        else
            req.set_dropfrom(false);
        printf("#####################  请输入你的操作: 道具eltem_Module_Base模块属性      #######################\n");
        Modelinfo *temp = req.add_mode();
        temp->set_modeltype(0);
        printf("#####################  请输入你的操作: 道具对应模块属性的eltem_Attribute_Attack值      #######################\n");
        temp->add_attributetype(0);
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        temp->add_attributetypevalue(atoi(buffer));
        printf("#####################  请输入你的操作: 道具对应模块属性的eltem_Attribute_HP值      #######################\n");
        temp->add_attributetype(1);
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        temp->add_attributetypevalue(atoi(buffer));
        printf("#####################  请输入你的操作: 道具eltem_Module_Power模块属性      #######################\n");
        temp = req.add_mode();
        temp->set_modeltype(1);
        printf("#####################  请输入你的操作: 道具对应模块属性的eltem_Attribute_Attack值      #######################\n");
        temp->add_attributetype(0);
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        temp->add_attributetypevalue(atoi(buffer));
        printf("#####################  请输入你的操作: 道具对应模块属性的eltem_Attribute_HP值      #######################\n");
        temp->add_attributetype(1);
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        temp->add_attributetypevalue(atoi(buffer));
        printf("#####################  请输入你的操作: 道具eltem_Module_Insert模块属性      #######################\n");
        temp = req.add_mode();
        temp->set_modeltype(2);
        printf("#####################  请输入你的操作: 道具对应模块属性的eltem_Attribute_Attack值      #######################\n");
        temp->add_attributetype(0);
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        temp->add_attributetypevalue(atoi(buffer));
        printf("#####################  请输入你的操作: 道具对应模块属性的eltem_Attribute_HP值      #######################\n");
        temp->add_attributetype(1);
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        temp->add_attributetypevalue(atoi(buffer));
        //------------------------------------------------------------------------------------------------------------------------------------

        head.m_message_len = (MESSAGE_HEAD_SIZE + req.ByteSize()) | (1 << 20);
        len = MESSAGE_HEAD_SIZE + req.ByteSize();
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
        */
        Addreq req;
        req.set_id(10);
        req.set_eltemtype(1);
        req.set_value(1);
        req.set_uid(6989);
        req.set_usemoney(false);
        req.set_pos(2);
        req.set_dropfrom(true);
        Modelinfo *temp = req.add_mode();
        temp->set_modeltype(0);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(30);
        temp = req.add_mode();
        temp->set_modeltype(1);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(-1);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(-1);
        temp = req.add_mode();
        temp->set_modeltype(2);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(-1);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(-1);
        head.m_message_len = (MESSAGE_HEAD_SIZE + req.ByteSize()) | (1 << 20);
        len = MESSAGE_HEAD_SIZE + req.ByteSize();
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
    }
    else if (atoi(buffer) == 3)
    {
        Addreq req;
        req.set_id(12);
        req.set_eltemtype(1);
        req.set_value(1);
        req.set_uid(6989);
        req.set_usemoney(false);
        req.set_pos(8);
        req.set_dropfrom(false);
        Modelinfo *temp = req.add_mode();
        temp->set_modeltype(0);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(30);
        temp = req.add_mode();
        temp->set_modeltype(1);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        temp = req.add_mode();
        temp->set_modeltype(2);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        head.m_message_len = (MESSAGE_HEAD_SIZE + req.ByteSize()) | (1 << 20);
        len = MESSAGE_HEAD_SIZE + req.ByteSize();
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
    }
    else if (atoi(buffer) == 4)
    {
        Addreq req;
        req.set_id(13);
        req.set_eltemtype(0);
        req.set_value(100);
        req.set_uid(6989);
        req.set_usemoney(false);
        req.set_pos(3);
        req.set_dropfrom(true);
        Modelinfo *temp = req.add_mode();
        temp->set_modeltype(0);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(30);
        temp = req.add_mode();
        temp->set_modeltype(1);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        temp = req.add_mode();
        temp->set_modeltype(2);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        head.m_message_len = (MESSAGE_HEAD_SIZE + req.ByteSize()) | (1 << 20);
        len = MESSAGE_HEAD_SIZE + req.ByteSize();
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
    }
    else if (atoi(buffer) == 5)
    {
        Addreq req;
        req.set_id(14);
        req.set_eltemtype(2);
        req.set_value(100);
        req.set_uid(6989);
        req.set_usemoney(false);
        req.set_pos(3);
        req.set_dropfrom(true);
        Modelinfo *temp = req.add_mode();
        temp->set_modeltype(0);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(30);
        temp = req.add_mode();
        temp->set_modeltype(1);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        temp = req.add_mode();
        temp->set_modeltype(2);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        head.m_message_len = (MESSAGE_HEAD_SIZE + req.ByteSize()) | (1 << 20);
        len = MESSAGE_HEAD_SIZE + req.ByteSize();
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
    }
    else if (atoi(buffer) == 6)
    {
        Addreq req;
        req.set_id(10);
        req.set_eltemtype(1);
        req.set_value(-1);
        req.set_uid(6989);
        req.set_usemoney(false);
        req.set_pos(3);
        req.set_inuse(true);
        req.set_dropfrom(true);
        Modelinfo *temp = req.add_mode();
        temp->set_modeltype(0);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(30);
        temp = req.add_mode();
        temp->set_modeltype(1);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        temp = req.add_mode();
        temp->set_modeltype(2);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        head.m_message_len = (MESSAGE_HEAD_SIZE + req.ByteSize()) | (1 << 20);
        len = MESSAGE_HEAD_SIZE + req.ByteSize();
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
    }
    else if (atoi(buffer) == 7)
    {
        Addreq req;
        req.set_id(14);
        req.set_eltemtype(2);
        req.set_value(-10);
        req.set_uid(6989);
        req.set_usemoney(false);
        req.set_pos(3);
        req.set_inuse(false);
        req.set_dropfrom(true);
        Modelinfo *temp = req.add_mode();
        temp->set_modeltype(0);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(30);
        temp = req.add_mode();
        temp->set_modeltype(1);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        temp = req.add_mode();
        temp->set_modeltype(2);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        head.m_message_len = (MESSAGE_HEAD_SIZE + req.ByteSize()) | (1 << 20);
        len = MESSAGE_HEAD_SIZE + req.ByteSize();
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
    }
    else if (atoi(buffer) == 8)
    {
        Addreq req;
        req.set_id(13);
        req.set_eltemtype(0);
        req.set_value(-50);
        req.set_uid(6989);
        req.set_usemoney(false);
        req.set_pos(3);
        req.set_inuse(false);
        req.set_dropfrom(true);
        Modelinfo *temp = req.add_mode();
        temp->set_modeltype(0);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(30);
        temp = req.add_mode();
        temp->set_modeltype(1);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        temp = req.add_mode();
        temp->set_modeltype(2);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        head.m_message_len = (MESSAGE_HEAD_SIZE + req.ByteSize()) | (1 << 20);
        len = MESSAGE_HEAD_SIZE + req.ByteSize();
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
    }
    else if (atoi(buffer) == 9)
    {
        Addreq req;
        req.set_id(10);
        req.set_eltemtype(1);
        req.set_value(-1);
        req.set_uid(6989);
        req.set_usemoney(false);
        req.set_pos(3);
        req.set_inuse(false);
        req.set_dropfrom(false);
        Modelinfo *temp = req.add_mode();
        temp->set_modeltype(0);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(30);
        temp = req.add_mode();
        temp->set_modeltype(1);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        temp = req.add_mode();
        temp->set_modeltype(2);
        temp->add_attributetype(0);
        temp->add_attributetypevalue(10);
        temp->add_attributetype(1);
        temp->add_attributetypevalue(10);
        head.m_message_len = (MESSAGE_HEAD_SIZE + req.ByteSize()) | (1 << 20);
        len = MESSAGE_HEAD_SIZE + req.ByteSize();
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
    }
    else if (atoi(buffer) == 2)
    {
        Packagereq req;
        printf("#####################  请输入你的操作: 查询的玩家的Id      #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        req.set_uid(atoi(buffer));
        printf("#####################  请输入你的操作: 从哪里读取数据 0:直接从服务器内存中读取  1:从redis中读取数据  2:从sql的数据库中读取数据      #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        req.set_init(atoi(buffer));

        head.m_message_len = (MESSAGE_HEAD_SIZE + req.ByteSize()) | (1 << 21);
        len = MESSAGE_HEAD_SIZE + req.ByteSize();
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
    }
    else if (atoi(buffer) == 0)
    {
        Reqest req;
        printf("#####################  请输入你的操作: 注册玩家的名字      #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        req.set_name(string("chenzun"));
        printf("#####################  请输入你的操作: 注册玩家的密码      #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        //req.set_password(string(buffer));
        req.set_password(string("123456"));
        printf("#####################  请输入你的操作: 注册玩家时需要发送的message      #######################\n");
        ret = read(STDIN_FILENO, buffer, sizeof(buffer));
        req.set_message(string(buffer));

        head.m_message_len = MESSAGE_HEAD_SIZE + req.ByteSize();
        len = head.m_message_len;
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
        /*
        Reqest req;
        req.set_name(string("chenzun"));
        req.set_password(string("123456"));
        req.set_message(string("register"));
        head.m_message_len = MESSAGE_HEAD_SIZE + req.ByteSize();
        len = head.m_message_len;
        int coded_length = 0;
        head.encode(data, coded_length);
        req.SerializePartialToArray(data + MESSAGE_HEAD_SIZE, req.ByteSize());
        */
    }

    int fd = m_client_conn_socket->get_fd();
    ret = m_client_conn_socket->send_data(data, (size_t)len);
    if (ret < success)
    {
        printf("Send Failed...........\n");
    }
    if (ret > success)
    {
        printf("Send %d Times Until finished......\n", ret);
    }
    printf("send msg  fd:%d    msglen = %d\n", fd, head.m_message_len);
    return;
}

int DemoClient::process_code(const char *pszInCode, const int iInCodeSize, int socketfd)
{
    if (!pszInCode || iInCodeSize <= 0)
    {
        return fail;
    }

    MsgHead stHead;
    if (success != stHead.decode(pszInCode, iInCodeSize))
    {
        printf("[Player::%s]head decode error\n", __FUNCTION__);
        return fail;
    }

    if (stHead.m_message_len != iInCodeSize)
    {
        printf("[Player::%s]the package size decoded from service was not equal with received size.\n", __FUNCTION__);
        return fail;
    }
    int iBodySize = stHead.m_message_len - MESSAGE_HEAD_SIZE;
    Response res;
    res.ParseFromArray(pszInCode + MESSAGE_HEAD_SIZE, iBodySize);
    cout << "Client Get Message From Server Player:[" << res.uid() << "]  Ack:[" << res.ack() << "]\n";
    return 0;
}