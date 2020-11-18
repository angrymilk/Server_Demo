#ifndef BASESERVER_H
#define BASESERVER_H
#include <map>
#include "Epoll.h"
#include "TCPSocket.h"

class BaseServer
{
public:
    void loop();
    typedef std::function<void()> Functor;
    BaseServer(std::string ip, int port) : m_ip(ip), m_port(port)
    {
        m_server_socket.reset(new TCPSocket());
    }

    ~BaseServer() {}
    int init();
    std::unordered_map<int, std::shared_ptr<TCPSocket>> m_sockets_map;

private:
    void wake_up_write();
    void wake_up_read();
    void do_pending_functions();
    void run_in_loop(Functor func);
    void handle_read();
    int epoll_recv();
    std::unordered_map<int, std::shared_ptr<TCPSocket>> m_sockets_map;
    std::shared_ptr<TCPSocket> m_server_socket;
    std::vector<Functor> m_pending_functor;
    std::string m_ip;
    int m_port;
    Epoll m_epoll;
    int m_wake_fd;
    int m_thread_id;
    std::mutex m_mutex;
    int m_wake_fd;
};
#endif