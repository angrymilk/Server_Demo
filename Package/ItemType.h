#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <vector>

enum EltemType
{
    eMoney,
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

struct ItemInfo
{
    EltemType mtype;
    std::vector<std::vector<EltemAttributeType>> mattrtype;
    std::vector<std::vector<int>> value;
    std::vector<EltemModuleType> mmotype;
    int id;
};