#ifndef PLAYER_H
#define PLAYER_H
#include "../Common/base.h"
#include "../Common/MesHead.h"
#include "../Common/Epoll.h"
#include "../Common/MesHandle.h"
#include <map>
#include <cstdio>

class Player
{
public:
    explicit Player(int uin)
    {
        m_uin = uin;
    }

    ~Player();

    int uin();

private:
    int m_uin;
};
#endif