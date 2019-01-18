#include "db_dataprovider.h"

#include <QDebug>

#include <QSqlError>
#include <QSqlQuery>

DB_DataProvider::DB_DataProvider( const QString &dbName )
{
    if( !QFile::exists(dbName) )
    {
        throw QString( "Error: DATABASE '" + dbName + "' not found" );
    }

    this->db = QSqlDatabase::addDatabase("QSQLITE");

    this->db.setDatabaseName( dbName );

    if( !db.open() )
    {
        throw QString("DB connecton failed");
    }
    else
    {
        qDebug() << "Database: connection ok";
    }

    this->db.open();
}

DB_DataProvider::~DB_DataProvider()
{
    this->db.close();
}

ShopItem DB_DataProvider::getShopItem( const QString &shopItemName ) const
{
    QSqlQuery query;

    if( query.exec("SELECT * FROM shopItem WHERE Name = '" + shopItemName + "'" ) )
    {
        if( query.next() )
        {
            const uint id = query.value(0).toUInt();
            const QString name = query.value(1).toString();

            return ShopItem{ id, name };
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
        return ShopItem{};
    }
}

ShopItem DB_DataProvider::getShopItem( const uint &shopItemID ) const
{
    QSqlQuery query;

    if( query.exec("SELECT * FROM shopItem WHERE ShopItemID = " + QString::number( shopItemID ) ) )
    {
        if( query.next() )
        {
            const uint id = query.value(0).toUInt();
            const QString name = query.value(1).toString();

            return ShopItem{ id, name };
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
        return ShopItem{};
    }
}

QString DB_DataProvider::getShopItemName( const uint &shopItemID  ) const
{
    QSqlQuery query;

    if( query.exec("SELECT * FROM shopItem WHERE ShopItemID = " + QString::number( shopItemID ) ) )
    {
        if( query.next() )
        {
            const QString name = query.value(1).toString();

            return name;
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
        return QString{};
    }
}

QList<ShopItem> DB_DataProvider::getShopItems() const
{
    QList<ShopItem> shopItems;

    QSqlQuery query;

    if( query.exec("SELECT * FROM shopItem") )
    {
        while( query.next() )
        {
            const uint id = query.value(0).toUInt();
            const QString name = query.value(1).toString();

            shopItems.append( ShopItem{ id, name } );
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
        return QList<ShopItem>{};
    }

    return shopItems;
}

Discounter DB_DataProvider::getDiscounter( const uint &discounterId ) const
{
    QSqlQuery query;

    if( query.exec("SELECT DiscounterID, Name, Location FROM discounter WHERE DiscounterID = " + QString::number( discounterId ) ) )
    {
        if( query.next() )
        {
            const uint id = query.value(0).toUInt();
            const QString name = query.value(1).toString();
            const QString location = query.value(2).toString();

            return Discounter{id, name, location};
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
        return Discounter{};
    }
}

QList<Discounter> DB_DataProvider::getDiscounters() const
{
    QList<Discounter> discounters;

    QSqlQuery query;

    if( query.exec("SELECT DiscounterID, Name, Location FROM discounter") )
    {
        while( query.next() )
        {
            const uint id = query.value(0).toUInt();
            const QString name = query.value(1).toString();
            const QString location = query.value(2).toString();

            discounters.append( Discounter{ id, name, location } );
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
        return QList<Discounter>{};
    }

    return discounters;
}

QList<DiscounterShopItem> DB_DataProvider::getLowPricedDiscounters( const uint &shopItemID ) const
{
    QList<DiscounterShopItem> discounterShopItems;

    QSqlQuery query;

    QString sql = "SELECT NormalPrice, ShopItemID, DiscounterID, OfferPrice ";
    sql += "FROM discounter_shopitem WHERE ShopItemID = " + QString::number( shopItemID ) + " " +
           "AND NormalPrice > 0.0 AND NormalPrice = (" +
            "SELECT MIN(NormalPrice) FROM discounter_shopitem WHERE ShopItemID = " +
            QString::number( shopItemID ) + " "  +
            "AND NormalPrice > 0.0)";

    if( query.exec( sql ) )
    {
        while( query.next() )
        {
            const uint shopItemID = query.value("ShopItemID").toUInt();
            const uint discounterID = query.value("DiscounterID").toUInt();
            const double normalPrice = query.value("NormalPrice").toDouble();
            const double offerPrice = query.value("OfferPrice").toDouble();

            discounterShopItems.append( DiscounterShopItem{ shopItemID, discounterID, normalPrice, offerPrice } );
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
        return QList<DiscounterShopItem>{};
    }

    return discounterShopItems;
}

QList<DiscounterShopItem> DB_DataProvider::getAllPricedDiscounters(const uint &shopItemID) const
{
    QList<DiscounterShopItem> discounterShopItems;

    QSqlQuery query;

    QString sql = "SELECT NormalPrice, ShopItemID, DiscounterID, OfferPrice ";
    sql += "FROM discounter_shopitem WHERE ShopItemID = " + QString::number( shopItemID ) + " " +
           "AND NormalPrice > 0.0";

    if( query.exec( sql ) )
    {
        while( query.next() )
        {
            const uint shopItemID = query.value("ShopItemID").toUInt();
            const uint discounterID = query.value("DiscounterID").toUInt();
            const double normalPrice = query.value("NormalPrice").toDouble();
            const double offerPrice = query.value("OfferPrice").toDouble();

            discounterShopItems.append( DiscounterShopItem{ shopItemID, discounterID, normalPrice, offerPrice } );
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
        return QList<DiscounterShopItem>{};
    }

    return discounterShopItems;
}


QList<DiscounterShopItem> DB_DataProvider::getDiscounterShopItems() const
{
    QList<DiscounterShopItem> discounterShopItems;

    QSqlQuery query;

    if( query.exec("SELECT ShopItemID, DiscounterID, NormalPrice, OfferPrice FROM discounter_shopitem") )
    {
        while( query.next() )
        {
            const uint shopItemID = query.value(0).toUInt();
            const uint discounterID = query.value(1).toUInt();
            const double normalPrice = query.value(2).toDouble();
            const double offerPrice = query.value(3).toDouble();

            discounterShopItems.append( DiscounterShopItem{ shopItemID, discounterID, normalPrice, offerPrice } );
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
        return QList<DiscounterShopItem>{};
    }

    return discounterShopItems;
}

QList<DiscounterShopItem> DB_DataProvider::getDiscounterShopItems( const uint &shopItemID ) const
{
    QList<DiscounterShopItem> discounterShopItems;

    QSqlQuery query;

    if( query.exec("SELECT ShopItemID, DiscounterID, NormalPrice, OfferPrice FROM discounter_shopitem WHERE ShopItemID = " + QString::number( shopItemID ) ) )
    {
        while( query.next() )
        {
            const uint shopItemID = query.value(0).toUInt();
            const uint discounterID = query.value(1).toUInt();
            const double normalPrice = query.value(2).toDouble();
            const double offerPrice = query.value(3).toDouble();

            discounterShopItems.append( DiscounterShopItem{ shopItemID, discounterID, normalPrice, offerPrice } );
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
        return QList<DiscounterShopItem>{};
    }

    return discounterShopItems;
}

uint DB_DataProvider::getLastShopItemId() const
{
    QSqlQuery query;

    if( query.exec( "SELECT MAX(ShopItemID) from shopitem" ) )
    {
        if( query.first() )
        {
            return query.value(0).toUInt();
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
    }

    return 0;
}

uint DB_DataProvider::getLastDiscounterId() const
{
    QSqlQuery query;

    if( query.exec( "SELECT MAX(DiscounterID) from discounter" ) )
    {
        if( query.first() )
        {
            return query.value(0).toUInt();
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
    }

    return 0;
}

void DB_DataProvider::insertIntoDiscounterShopItem( const uint &shopItemId,
                                   const uint &discounterId,
                                   const double &normalPrice,
                                   const double &offerPrice ) const
{
    QSqlQuery query;


    const QString sql = "INSERT OR IGNORE INTO discounter_shopitem(ShopItemID, DiscounterID, NormalPrice, OfferPrice) VALUES ("
            + QString::number( shopItemId ) + ","
            + QString::number( discounterId ) + ","
            + QString::number( normalPrice ) + ","
            + QString::number( offerPrice ) + ")";
            /*
            + "ON DUPLICATE KEY UPDATE NormalPrice= " + QString::number( normalPrice ) + ","
            + " OfferPrice= " + QString::number( offerPrice );
                    */

    const QString sql2 = "UPDATE discounter_shopitem SET NormalPrice= " + QString::number( normalPrice ) + ","
            + " OfferPrice= " + QString::number( offerPrice )
            + " WHERE ShopItemID = " + QString::number( shopItemId ) + " AND"
            + " DiscounterID = " + QString::number( discounterId ) + ";";

    qDebug() << sql;

    qDebug() << sql2;

    if( query.exec(sql) )
    {
        if( query.exec(sql2) )
        {
        }
        else
        {
            qDebug() << "query.exec()-Error: " << this->db.lastError();
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
    }
}

void DB_DataProvider::deleteShopItem( const uint &shopItemId ) const
{
    QSqlQuery query;

    const QString sql = "DELETE FROM shopitem WHERE ShopItemID = " + QString::number( shopItemId );

    qDebug() << sql;

    if( query.exec( sql ) )
    {
        qDebug() << "deleted";
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
    }
}

void DB_DataProvider::deleteDiscounter( const uint &discounterId ) const
{
    QSqlQuery query;

    const QString sql = "DELETE FROM discounter WHERE DiscounterID = " + QString::number( discounterId );

    qDebug() << sql;

    if( query.exec( sql ) )
    {
        qDebug() << "deleted";
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
    }
}

QSqlError DB_DataProvider::lastError()
{
    return this->db.lastError();
}

void DB_DataProvider::insertShopItem( const uint &shopItemId, const QString &newName )
{
    QSqlQuery query;

    QString sql;

    if( shopItemId != 0 )
    {
        sql = "INSERT OR IGNORE INTO shopitem(ShopItemID,Name) "
            "VALUES(" + QString::number( shopItemId ) + ",'" + newName + "')";
    }
    else
    {
        sql = "INSERT OR IGNORE INTO shopitem(Name) "
            "VALUES('" + newName + "')";
    }

    const QString sql2 = "UPDATE shopitem SET Name = '" + newName + "' WHERE "
                         "ShopItemID = " + QString::number( shopItemId );

    qDebug() << sql;

    if( query.exec( sql ) )
    {
        if( query.exec(sql2) )
        {
            qDebug() << "ok";
        }
        else
        {
            qDebug() << "query.exec()-Error: " << this->db.lastError();
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
    }
}

void DB_DataProvider::insertDiscounter( const uint &discounterId, const QString &newName, const QString &newLocation )
{
    QSqlQuery query;

    QString sql;

    if( discounterId != 0 )
    {
        sql = "INSERT OR IGNORE INTO discounter(DiscounterID,Name,Location) "
            "VALUES(" + QString::number( discounterId ) + ",'" + newName + "','" + newLocation + "')";
    }
    else
    {
        sql = "INSERT OR IGNORE INTO discounter(Name,Location) "
            "VALUES('" + newName + "','" + newLocation + "')";
    }

    const QString sql2 = "UPDATE discounter SET Name = '" + newName + "', Location='" + newLocation + "' WHERE "
                         "DiscounterID = " + QString::number( discounterId );

    qDebug() << sql;

    if( query.exec( sql ) )
    {
        if( query.exec(sql2) )
        {
            qDebug() << "ok";
        }
        else
        {
            qDebug() << "query.exec()-Error: " << this->db.lastError();
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
    }
}

double DB_DataProvider::getOfferPrice(const uint &shopItemId, const uint &discounterId) const
{
    QSqlQuery query;

    const QString sql = "SELECT * FROM discounter_shopitem WHERE ShopItemID = "
            + QString::number( shopItemId ) +" AND DiscounterID = "
            + QString::number( discounterId );

    if( query.exec( sql ) )
    {
        if( query.first() )
        {
            const double offerPrice = query.value("OfferPrice").toDouble();
            return offerPrice;
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
    }

    return 0.0;
}

double DB_DataProvider::getNormalPrice(const uint &shopItemId, const uint &discounterId) const
{
    QSqlQuery query;

    const QString sql = "SELECT * FROM discounter_shopitem WHERE ShopItemID = "
            + QString::number( shopItemId ) +" AND DiscounterID = "
            + QString::number( discounterId );

    if( query.exec( sql ) )
    {
        if( query.first() )
        {
            const double normalPrice = query.value("NormalPrice").toDouble();
            return normalPrice;
        }
    }
    else
    {
        qDebug() << "query.exec()-Error: " << this->db.lastError();
    }

    return 0.0;
}
