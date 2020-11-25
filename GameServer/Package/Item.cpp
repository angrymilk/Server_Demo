#include "Item.h"

int AbstractItem::get_eltem_type()
{
    return m_eltem_type;
}

void AbstractItem::set_eltem_type(EltemType type)
{
    m_eltem_type = type;
}

void AbstracItem::get_id()
{
    return uid;
}

void AbstracItem::set_id(int id)
{
    uid = id;
}

void ItemAttribute::set_attribute(EltemAttributeType type, int value)
{
    m_attribute_map[type] = value;
}

int ItemAttribute::get_attribute(EltemAttributeType type)
{
    return m_attribute_map[type];
}

void Item::set_id(int id)
{
    AbstracItem::set_id(id);
}

int Item::get_id()
{
    return AbstracItem::get_id();
}