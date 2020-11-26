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

int Player::add(ItemInfo info, int pos, int value)
{
    return m_package->add(info, pos, value);
}

std::shared_ptr<AbstractItem> Player::consume(int id, int value)
{
    return m_package->consume(id, value);
}