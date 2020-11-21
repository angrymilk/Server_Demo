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
    Player() {}
    ~Player();

    int uin();
    int get_id() const
    {
        return m_uin;
    }

    int move();
    int attack();
    int assist();
    std::string m_name;
    int m_uin;
    int dirx, diry, dirz, trgx, trgy, trgz, speed, time, hp, hs, attack_id;
    bool m_is_cheat;
};
#endif