#ifndef SHOPITEM_H
#define SHOPITEM_H

#include <QString>
#include <QVariant>

class ShopItem
{
public:
    ShopItem();
    explicit ShopItem( const uint &id );
    explicit ShopItem( const uint &id, const QString &name );

    const uint& getId() const;
    const QString& getName() const;

    bool operator<( const ShopItem &obj );

private:
    uint id;
    QString name;
};

#endif // SHOPITEM_H
