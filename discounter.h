#ifndef DISCOUNTER_H
#define DISCOUNTER_H

#include "shopitem.h"

class Discounter
{
public:
    Discounter();
    Discounter( const ulong &id, const QString &name, const QString &location );

    // bool addShopItem( const ShopItem &shopItem );

    const ulong& getId() const;
    const QString& getName() const;
    const QString& getLocation() const;

    QString toString() const;

    bool operator<( const Discounter &obj );

private:
    ulong id;
    QString name;
    QString location;
};

#endif // DISCOUNTER_H
