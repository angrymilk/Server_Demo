#include "itemtype.h"
#include <unordered_map>
class ItemInterface
{
public:
    virtual int get_eltem_type() = 0;
    virtual int set_eltem_type() = 0;
    virtual void set_attribute_type() = 0;
    virtual int get_attribute_type() = 0;
    virtual int get_uid() = 0;
    virtual void set_uid() = 0;
    virtual void init() = 0;
    virtual void to_string(std::string &out) = 0;
};

class AbstractItem : public ItemInterface
{
public:
    int get_eltem_type();
    int set_eltem_type();
    void set_attribute_type();
    int get_attribute_type();
    int get_uid();
    void set_uid();
    void init();
    //扩展标记位
    int m_flag_bit;

private:
    bool m_save;
    int m_count;
    int uid;
    EltemType m_eltem_type;
};

class ItemAttribute
{
public:
    ItemAttribute(std::shared_ptr<Item> point) : m_item(point) {}
    void set_attribute(EltemAttributeType type, int value);
    int get_attribute(EltemAttributeType type);

private:
    std::unordered_map<EltemAttributeType, int> m_attribute_map;
    std::shared_ptr<Item> m_item;
};

class Item : public AbstractItem
{
public:
    int get_eltem_type();
    int set_eltem_type();
    void set_attribute_type();
    int get_attribute_type();
    int get_uid();
    void set_uid();
    void init();
    //扩展标记位
    int m_flag_bit;

private:
    int uid;
};