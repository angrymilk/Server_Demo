#ifndef BASESERVER_H
#define BASESERVER_H
#include <map>
#include "Epoll.h"
#include "TCPSocket.h"

class BaseServer
{
public:
    BaseServer(std::string ip, int port) : m_ip(ip), m_port(port)
    {
        m_server_socket.reset(new TCPSocket());
    }

    ~BaseServer() {}
    int init();
    int epoll_recv();
    std::unordered_map<int, std::shared_ptr<TCPSocket>> m_sockets_map;

private:
    virtual int parsing_and_send(const char *pszInCode, const int iInCodeSize, int socketfd) = 0;
    std::shared_ptr<TCPSocket> m_server_socket;
    std::string m_ip;
    int m_port;
    Epoll m_epoll;
};
#endif