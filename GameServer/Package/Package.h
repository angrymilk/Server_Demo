#include "Money.h"
#include "Consume.h"
#include "Equip.h"
#include "ItemFactory.h"
#include <vector>
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

    int add(ItemInfo info, int pos, int value)
    {
        if (info.mtype == EltemType::eMoney)
        {
            if (m_vec[0][0] == nullptr)
                m_vec[0][0] = m_factory.create(info);
            m_vec[0][0]->set_amount(value);
        }
        else if (info.mtype == EltemType::eEQUIP)
        {
            if (m_posmap.find(info.id) != m_posmap.end())
            {
                pos = m_posmap[info.id].second;
                m_vec[1][pos]->set_amount(value + m_vec[1][pos]->get_amount());
            }
            else
            {
                m_vec[1][pos] = m_factory.create(info);
                m_posmap[info.id] = make_pair(1, pos);
            }
        }
        else if (info.mtype == EltemType::eCONSUME)
        {
            if (m_posmap.find(info.id) != m_posmap.end())
            {
                pos = m_posmap[info.id].second;
                m_vec[2][pos]->set_amount(value + m_vec[2][pos]->get_amount());
            }
            else
            {
                m_vec[2][pos] = m_factory.create(info);
                m_posmap[info.id] = make_pair(2, pos);
            }
        }
        else
            return -1;
        return 0;
    }

    int consume(int id, int value)
    {
        if (m_posmap.find(id) != m_posmap.end())
        {
            int tmp = m_vec[m_posmap[id].first][m_posmap[id].second]->get_amount();
            m_vec[m_posmap[id].first][m_posmap[id].second]->set_amount(tmp - value);
        }
        else
            return -1;
        return 0;
    }

private:
    std::vector<std::vector<std::shared_ptr<AbstractItem>>> m_vec;
    std::unordered_map<int, pair<int, int>> m_posmap;
    std::vector<int> m_num;
    ItemFactory m_factory;
};