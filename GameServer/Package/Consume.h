#include "Item.h"
class Consume : public Item
{
public:
    void init()
    {
    }

    int get_uid()
    {
        return Item::get_id();
    }

    void set_uid(int id)
    {
        Item::set_id(id);
    }

    void set_eltem_type(EltemType type)
    {
        Item::set_eltem_type(type);
    }

    int get_eltem_type()
    {
        return Item::get_eltem_type();
    }
};
