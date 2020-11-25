#include "ItemType.h"
#include <unordered_map>
#include <memory>
class ItemInterface
{
public:
    virtual int get_eltem_type() = 0;
    virtual void set_eltem_type(EltemType type) = 0;
    virtual void set_attribute(EltemModuleType mtype, EltemAttributeType type, int value) = 0;
    virtual int get_attribute(EltemModuleType mtype, EltemAttributeType type) = 0;
    virtual int get_uid() = 0;
    virtual void set_uid(int id) = 0;
    virtual void set_amount(int num) = 0;
    virtual int get_amount() = 0;
    virtual void init() = 0;
    virtual void to_string(std::string &out) = 0;
};

class AbstractItem : public ItemInterface
{
public:
    int get_eltem_type();
    void set_eltem_type(EltemType type);
    void set_attribute(EltemModuleType mtype, EltemAttributeType type, int value);
    int get_attribute(EltemModuleType mtype, EltemAttributeType type);
    int get_uid();
    void set_uid(int id);
    void set_amount(int num);
    int get_amount();
    void init();
    void to_string(std::string &out);
    //扩展标记位
    int m_flag_bit;

private:
    bool m_save;
    int m_count;
    int uid;
    EltemType m_eltem_type;
};

class Item;
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
    void set_eltem_type(EltemType type);
    void set_attribute(EltemModuleType mtype, EltemAttributeType type, int value);
    int get_attribute(EltemModuleType mtype, EltemAttributeType type);
    void set_amount(int num);
    int get_amount();
    int get_uid();
    void set_uid(int id);
    void init();
    //扩展标记位
    int m_flag_bit;

private:
    std::unordered_map<EltemModuleType, std::shared_ptr<ItemAttribute>> m_map;
};