#include <unordered_map>
enum EltemType
{
    Money,
    eCONSUME,
    eEQUIP,
    unused,
};

enum EltemAttributeType
{
    eltem_Attribute_Attack,
    eltem_Attribute_HP,
    unused,
};

enum EltemModuleType
{
    eltem_Module_Base,
    eltem_Module_Power,
    eltem_Module_Insert,
    unused,
};

struct iteminfo
{
    EltemType mtype;
    EltemAttributeType mattrtype;
    EltemModuleType mmotype;
    std::unordered_map<>;
};