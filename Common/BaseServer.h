#ifndef BASESERVER_H
#define BASESERVER_H
#include <map>
#include "Epoll.h"
#include "TCPSocket.h"
typedef std::function<void()> Functor;

class BaseServer
{
public:
    void loop();
    BaseServer(std::string ip, int port, ReadFunctor read_func) : m_ip(ip), m_port(port), m_read_func(std::move(read_func))
    {
        m_server_socket.reset(new TCPSocket(this));
    }

    ~BaseServer() {}
    int init();
    void run_in_loop(Functor func);
    int run();
    std::unordered_map<int, std::shared_ptr<TCPSocket>> m_sockets_map;

private:
    void wake_up_write();
    void wake_up_read();
    void do_pending_functions();
    void handle_read();
    int epoll_recv();
    std::shared_ptr<TCPSocket> m_server_socket;
    std::vector<Functor> m_pending_functor;
    ReadFunctor m_read_func;
    std::string m_ip;
    int m_port;
    Epoll m_epoll;
    int m_wake_fd;
    int m_thread_id;
    std::mutex m_mutex;
};
#endif