#include "Money.h"
#include "Consume.h"
#include "Equip.h"
#include "ItemFactory.h"

class Package
{
public:
    Package()
    {
        m_vec.resize(3);
        m_num.resize(3);
        m_num[0] = m_num[1] = m_num[2] = 0;
        m_vec[0].resize(1);
        m_vec[1].resize(10);
        m_vec[2].resize(10);
    }
    void insert()
    {
    }

    void use()
    {
    }

private:
    std::vector<std::vector<AbstractItem>> m_vec;
    std::vector<int> m_num;
};