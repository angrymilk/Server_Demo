#include "Item.h"
//  AbstractItem    ######################################################################################################
int AbstractItem::get_eltem_type()
{
    return m_eltem_type;
}

void AbstractItem::set_eltem_type(EltemType type)
{
    m_eltem_type = type;
}

int AbstractItem::get_uid()
{
    return uid;
}

void AbstractItem::set_uid(int id)
{
    uid = id;
}

void AbstractItem::set_amount(int num)
{
    m_count = num;
}

int AbstractItem::get_amount()
{
    return m_count;
}
// Item    ##########################################################################################################
void Item::set_uid(int id)
{
    AbstractItem::set_uid(id);
}

int Item::get_uid()
{
    return AbstractItem::get_uid();
}

void Item::set_amount(int num)
{
    AbstractItem::set_amount(num);
}

int Item::get_amount()
{
    return AbstractItem::get_amount();
}

int Item::get_eltem_type()
{
    return AbstractItem::get_eltem_type();
}

void Item::set_eltem_type(EltemType type)
{
    AbstractItem::set_eltem_type(type);
}
// ItemAttribute     #####################################################################################################
void ItemAttribute::set_attribute(EltemAttributeType type, int value)
{
    m_attribute_map[type] = value;
}

int ItemAttribute::get_attribute(EltemAttributeType type)
{
    return m_attribute_map[type];
}