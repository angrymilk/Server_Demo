#include "Item.h"
class Consume : public Item
{
public:
    void init()
    {
    }

    int get_uid()
    {
        return Item::get_uid();
    }

    void set_uid(int id)
    {
        Item::set_uid(id);
    }

    void set_eltem_type(EltemType type)
    {
        Item::set_eltem_type(type);
    }

    int get_eltem_type()
    {
        return Item::get_eltem_type();
    }

    int get_amount()
    {
        return Item::get_amount();
    }

    void set_amount(int num)
    {
        Item::set_amount(num);
    }

    void set_attribute(EltemModuleType mtype, EltemAttributeType type, int value)
    {
    }

    int get_attribute(EltemModuleType mtype, EltemAttributeType type)
    {
    }
};
