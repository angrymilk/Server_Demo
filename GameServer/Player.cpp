#include "Player.h"

Player::~Player()
{
}

int Player::uin()
{
    return m_uin;
}

void Player::set_uin(int id)
{
    m_uin = id;
}