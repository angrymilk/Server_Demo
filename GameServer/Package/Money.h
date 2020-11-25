#include "Item.h"
class Money : public AbstractItem
{
public:
    void init()
    {
    }

    int get_uid()
    {
        return AbstracItem::get_id();
    }

    void set_uid(int id)
    {
        AbstracItem::set_id(id);
    }

    void set_eltem_type(EltemType type)
    {
        AbstracItem::set_eltem_type(type);
    }

    int get_eltem_type()
    {
        return AbstracItem::get_eltem_type();
    }
};