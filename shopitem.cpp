#include "shopitem.h"

ShopItem::ShopItem()
: ShopItem{ 0u, "" }
{
}

ShopItem::ShopItem( const uint &id, const QString &name )
: id{ id }
, name{ name }
{
}

const uint& ShopItem::getId() const
{
    return this->id;
}

const QString& ShopItem::getName() const
{
    return this->name;
}

bool ShopItem::operator<( const ShopItem &obj )
{
    return this->name < obj.name;
}
