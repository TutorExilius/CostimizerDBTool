#include "discountershopitem.h"

#include <QString>

DiscounterShopItem::DiscounterShopItem( const ulong &shopItemId, const ulong &discounterId,
       const double &normalPrice, const double &offerPrice )
: shopItemId{ shopItemId }
, discounterId{ discounterId }
, normalPrice{ normalPrice }
, offerPrice{ offerPrice }
{
}

ulong DiscounterShopItem::getDiscounterId() const
{
    return this->discounterId;
}

ulong DiscounterShopItem::getShopItemId() const
{
    return this->shopItemId;
}

double DiscounterShopItem::getNormalPrice() const
{
    return this->normalPrice;
}

double DiscounterShopItem::getOfferPrice() const
{
    return this->offerPrice;
}

void DiscounterShopItem::setNormalPrice( const double &normalPrice )
{
    this->normalPrice = normalPrice;
}

void DiscounterShopItem::setOfferPrice( const double &offerPrice )
{
    this->offerPrice = offerPrice;
}

QString DiscounterShopItem::toString() const
{
    QString outStr;

    outStr += "ShopID:\t" + QString::number( this->getShopItemId() ) + "\n";
    outStr += "Normal:\t" + QString::number( this->getNormalPrice() ) + "\n";
    outStr += "Angebot:\t" + QString::number( this->getOfferPrice() ) + "\n";
    outStr += "DiscounterID:\t" + QString::number(   this->getDiscounterId() ) + "\n";

    return outStr;
}

