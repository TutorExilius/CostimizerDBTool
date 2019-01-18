#ifndef DB_DATAPROVIDER_H
#define DB_DATAPROVIDER_H

#include <QList>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "discounter.h"
#include "discountershopitem.h"
#include "shopitem.h"

class DB_DataProvider
{
public:
    DB_DataProvider( const QString &dbName );
    ~DB_DataProvider();

    ShopItem getShopItem( const QString &shopItemName ) const;
    ShopItem getShopItem( const uint &shopItemID ) const;
    QString getShopItemName( const uint &shopItemID  ) const;
    QList<ShopItem> getShopItems() const;
    Discounter getDiscounter( const uint &discounterID ) const;
    QList<Discounter> getDiscounters() const;
    QList<DiscounterShopItem> getLowPricedDiscounters( const uint &shopItemID ) const;
    QList<DiscounterShopItem> getAllPricedDiscounters( const uint &shopItemID ) const;
    QList<DiscounterShopItem> getDiscounterShopItems() const;
    QList<DiscounterShopItem> getDiscounterShopItems( const uint &shopItemID ) const;
    uint getLastShopItemId() const;
    uint getLastDiscounterId() const;

    QSqlError lastError();
    void insertShopItem( const uint &shopItemId, const QString &newName );
    void insertDiscounter( const uint &discounterId,
                           const QString &newName,
                           const QString &newLocation );
    void insertIntoDiscounterShopItem( const uint &shopItemId,
                                       const uint &discounterId,
                                       const double &normalPrice,
                                       const double &offerPrice ) const;
    void deleteShopItem( const uint &shopItemId ) const;
    void deleteDiscounter( const uint &discounterId ) const;

    double getOfferPrice(  const uint &shopItemId, const uint &discounterId ) const;
    double getNormalPrice(  const uint &shopItemId, const uint &discounterId ) const;


private:
    QString dbName;
    QSqlDatabase db;
};

#endif // DB_DATAPROVIDER_H
