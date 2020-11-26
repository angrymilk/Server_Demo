#ifndef PLAYER_H
#define PLAYER_H
#include "../Common/base.h"
#include "../Common/MesHead.h"
#include "../Common/Epoll.h"
#include "../Common/MesHandle.h"
#include <map>
#include <cstdio>
#include "Package/Package.h"

class Player
{
public:
    explicit Player(int uin)
    {
        m_uin = uin;
    }

    ~Player();

    void set_uin(int id);

    int uin();

private:
    int m_uin;
    std::shared_ptr<Package> m_package;
};
#endif