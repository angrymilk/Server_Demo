#include "Item.h"
#include "Money.h"
#include "Equip.h"
#include "Consume.h"

class ItemFactory
{
public:
    ItemFactory() {}
    std::shared_ptr<AbstractItem> create(ItemInfo info)
    {
        if (info.mtype == EltemType::eMoney)
            return std::make_shared<Money>(info);
        else if (info.mtype == EltemType::eEQUIP)
            return std::make_shared<Equip>(info);
        else if (info.mtype == EltemType::eCONSUME)
            return std::make_shared<Consume>(info);
        else
            return nullptr;
    }
};