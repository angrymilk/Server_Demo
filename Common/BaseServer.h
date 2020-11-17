#ifndef BASESERVER_H
#define BASESERVER_H
#include <map>
#include "Epoll.h"
#include "TCPSocket.h"

class BaseServer
{
public:
    typedef std::function<void()> Functor;

    void loop();
    BaseServer(std::string ip, int port) : m_ip(ip), m_port(port)
    {
        m_server_socket.reset(new TCPSocket());
    }

    ~BaseServer() {}
    int init();
    std::unordered_map<int, std::shared_ptr<TCPSocket>> m_sockets_map;

private:
    void wakeup();
    void do_pending_functions();
    void send(const char *buff);
    void handle_read();
    int epoll_recv();
    std::unordered_map<int, std::shared_ptr<TCPSocket>> m_sockets_map;
    std::shared_ptr<TCPSocket> m_server_socket;
    std::string m_ip;
    int m_port;
    Epoll m_epoll;
    int m_wake_fd;
    bool m_looping;
};
#endif