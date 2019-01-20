#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QVariant>

#include <algorithm>

#include "shopitemdialog.h"
#include "configdialog.h"
#include "discounterdialog.h"

#include "db_dataprovider.h"

MainWindow::MainWindow( QWidget *parent )
: QMainWindow{ parent }
, ui{ new Ui::MainWindow }
, dbDataProvider{ nullptr }
, config{ QCoreApplication::applicationDirPath() + "/config.txt" }
{
    this->ui->setupUi(this);

    const QString database = this->config.getValueOf("Database");
    this->dbDataProvider = new DB_DataProvider{ database };

    const double FACTOR = 1.7;

    QFontMetrics metrics = this->ui->textEdit_normalPrice->fontMetrics();
    this->ui->textEdit_normalPrice->setMinimumHeight( static_cast<int>( metrics.height() * FACTOR ) );
    this->ui->textEdit_normalPrice->setMaximumHeight( static_cast<int>( metrics.height() * FACTOR ) );

    QFontMetrics metrics2 = this->ui->textEdit_offerPrice->fontMetrics();
    this->ui->textEdit_offerPrice->setMinimumHeight( static_cast<int>( metrics2.height() * FACTOR ) );
    this->ui->textEdit_offerPrice->setMaximumHeight( static_cast<int>( metrics2.height() * FACTOR ) );

    QFontMetrics metrics3 = this->ui->comboBox_shopItem->fontMetrics();
    this->ui->comboBox_shopItem->setMinimumHeight( static_cast<int>( metrics3.height() * FACTOR ) );
    this->ui->comboBox_shopItem->setMaximumHeight( static_cast<int>( metrics3.height() * FACTOR ) );

    QFontMetrics metrics4 = this->ui->comboBox_discounter->fontMetrics();
    this->ui->comboBox_discounter->setMinimumHeight( static_cast<int>( metrics4.height() * FACTOR ) );
    this->ui->comboBox_discounter->setMaximumHeight( static_cast<int>( metrics4.height() * FACTOR ) );

    const int buttonHeight = this->ui->comboBox_shopItem->height() + 2;

    // Add Button - ShopItem
    this->ui->pushButton_addNewShopItem->setMinimumHeight( buttonHeight );
    this->ui->pushButton_addNewShopItem->setMaximumHeight( buttonHeight );
    this->ui->pushButton_addNewShopItem->setMinimumWidth( buttonHeight );
    this->ui->pushButton_addNewShopItem->setMaximumWidth( buttonHeight );

    // Remove Button - ShopItem
    this->ui->pushButton_removeShopItem->setMinimumHeight( buttonHeight );
    this->ui->pushButton_removeShopItem->setMaximumHeight( buttonHeight );
    this->ui->pushButton_removeShopItem->setMinimumWidth( buttonHeight );
    this->ui->pushButton_removeShopItem->setMaximumWidth( buttonHeight );

    // Add Button - Discounter
    this->ui->pushButton_addNewDiscounter->setMinimumHeight( buttonHeight );
    this->ui->pushButton_addNewDiscounter->setMaximumHeight( buttonHeight );
    this->ui->pushButton_addNewDiscounter->setMinimumWidth( buttonHeight );
    this->ui->pushButton_addNewDiscounter->setMaximumWidth( buttonHeight );

    // Remove Button - Discounter
    this->ui->pushButton_removeDiscounter->setMinimumHeight( buttonHeight );
    this->ui->pushButton_removeDiscounter->setMaximumHeight( buttonHeight );
    this->ui->pushButton_removeDiscounter->setMinimumWidth( buttonHeight );
    this->ui->pushButton_removeDiscounter->setMaximumWidth( buttonHeight );


    // Edit Button - ShopItem
    this->ui->pushButton_editShopItem->setMinimumHeight( buttonHeight );
    this->ui->pushButton_editShopItem->setMaximumHeight( buttonHeight );

    // Edit Button - Discounter
    this->ui->pushButton_editDiscounter->setMinimumHeight( buttonHeight );
    this->ui->pushButton_editDiscounter->setMaximumHeight( buttonHeight );

    this->adjustSize();
    this->setMaximumSize( this->size() );

    this->loadShopItems();
    this->loadDiscounter();

    QObject::connect( this, &MainWindow::saved,
                      this, &MainWindow::onSaved,
                      Qt::UniqueConnection );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateShopItemDBData( const uint &shopItemId, const QString &newName )
{
    this->dbDataProvider->insertShopItem( shopItemId, newName );
}

void MainWindow::updateDiscounterDBData( const uint &discounterId, const QString &newName, const QString &newLocation )
{
    this->dbDataProvider->insertDiscounter( discounterId,
                                            newName,
                                            newLocation );
}

void MainWindow::saveConfig(const Config config)
{
    this->config = config;
    this->config.writeConfigFile();
}

void MainWindow::onShopItemDialogOkClicked( const uint &shopItemId )
{
    this->loadShopItems();

    QString shopItemName;

    if( shopItemId != 0 )
    {
        shopItemName = this->cachedShopItems.key( shopItemId );
    }
    else
    {
        const uint lastShopItemId = this->dbDataProvider->getLastShopItemId();
        shopItemName = this->cachedShopItems.key( lastShopItemId );
    }

    this->ui->comboBox_shopItem->setCurrentText( shopItemName );
}

void MainWindow::onDiscounterDialogOkClicked( const uint &discounterId )
{
    this->loadDiscounter();

    QString discounterName;

    if( discounterId != 0 )
    {
        discounterName = this->cachedShopItems.key( discounterId );
    }
    else
    {
        const uint lastDiscounterId = this->dbDataProvider->getLastDiscounterId();
        discounterName = this->cachedDiscounters.key( lastDiscounterId );
    }

    this->ui->comboBox_discounter->setCurrentText( discounterName );
}

void MainWindow::on_action_About_Qt_triggered()
{
    QMessageBox::aboutQt( this );
}

void MainWindow::on_action_Close_triggered()
{
    this->close();
}

void MainWindow::on_action_Settings_triggered()
{
    qDebug() << "Settings...";

    ConfigDialog *settings = new ConfigDialog{ this, this->config };
    settings->exec();
}

void MainWindow::on_pushButton_addNewDiscounter_clicked()
{
    DiscounterDialog *dialog = new DiscounterDialog( this, "&Hinzufügen", "", "" );

    QObject::connect( dialog, &DiscounterDialog::discounterDialogOkClick,
                      this, &MainWindow::onDiscounterDialogOkClicked,
                      Qt::UniqueConnection );

    dialog->exec();
}

QList<ShopItem> MainWindow::getShopItems() const
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
        qDebug() << "query.exec()-Error: " << this->dbDataProvider->lastError().text();
        return QList<ShopItem>{};
    }

    return shopItems;
}

void MainWindow::loadShopItems()
{
    this->cachedShopItems.clear();
    this->ui->comboBox_shopItem->clear();

    QList<ShopItem> shopItems = this->dbDataProvider->getShopItems();

    std::sort( shopItems.begin(), shopItems.end() );

    for( const auto &shopItem : shopItems )
    {
        const QString itemText = shopItem.getName();

        this->ui->comboBox_shopItem->addItem( itemText );
        this->cachedShopItems.insert( itemText, shopItem.getId() );
    }

    if( this->cachedShopItems.isEmpty() )
    {
        this->ui->pushButton_removeShopItem->setEnabled( false );
        this->ui->pushButton_editShopItem->setEnabled( false );
    }
    else
    {
        this->ui->pushButton_removeShopItem->setEnabled( true );
        this->ui->pushButton_editShopItem->setEnabled( true );
    }

    this->updateData();
    this->updateSaveButtonView();
}

void MainWindow::loadDiscounter()
{
    this->cachedDiscounters.clear();
    this->ui->comboBox_discounter->clear();

    QList<Discounter> discounters = this->dbDataProvider->getDiscounters();

    std::sort( discounters.begin(), discounters.end() );

    for( const auto &discounter : discounters )
    {
        const QString itemText = discounter.getName() + " (" + discounter.getLocation() +")";

        this->ui->comboBox_discounter->addItem( itemText );
        this->cachedDiscounters.insert( itemText, discounter.getId() );
    }

    if( this->cachedDiscounters.isEmpty() )
    {
        this->ui->pushButton_removeDiscounter->setEnabled( false );
        this->ui->pushButton_editDiscounter->setEnabled( false );
    }
    else
    {
        this->ui->pushButton_removeDiscounter->setEnabled( true );
        this->ui->pushButton_editDiscounter->setEnabled( true );
    }

    this->updateData();
    this->updateSaveButtonView();
}

void MainWindow::updateSaveButtonView()
{
    if( this->ui->comboBox_shopItem->currentText().isEmpty() ||
        this->ui->comboBox_discounter->currentText().isEmpty() )
    {
        this->ui->pushButton_save->setEnabled( false );
    }
    else
    {
        this->ui->pushButton_save->setEnabled( true );
    }
}

void MainWindow::updateData()
{
    if( !this->cachedShopItems.isEmpty() && !this->cachedDiscounters.isEmpty() )
    {
        const uint shopItemdId = this->cachedShopItems[this->ui->comboBox_shopItem->currentText()];
        const uint discounterId = this->cachedDiscounters[this->ui->comboBox_discounter->currentText()];

        const double normalPrice = this->dbDataProvider->getNormalPrice( shopItemdId, discounterId );
        const double offerPrice = this->dbDataProvider->getOfferPrice( shopItemdId, discounterId );

        this->ui->textEdit_normalPrice->setText( QString::number( normalPrice ) );
        this->ui->textEdit_offerPrice->setText( QString::number( offerPrice ) );
    }
}

void MainWindow::on_pushButton_save_clicked()
{
    const QString discounterSelected = this->ui->comboBox_discounter->currentText();
    const QString shopItemSelected = this->ui->comboBox_shopItem->currentText();

    const uint discounterId = this->cachedDiscounters[discounterSelected];
    const uint shopItemId = this->cachedShopItems[shopItemSelected];

    bool ok = true;
    double normalPrice = 0.0;
    double offerPrice = 0.0;

    if( !this->ui->textEdit_normalPrice->text().isEmpty() )
    {
        normalPrice = this->ui->textEdit_normalPrice->text().replace(',','.').toDouble( &ok );
    }

    if( !ok )
    {
        qDebug() << "Normal-Price muss ein Zahlen-Wert sein!";

        emit saved( false );

        return;

        // throw "Normal-Price muss ein Zahlen-Wert sein!";
    }

    if( !this->ui->textEdit_offerPrice->text().isEmpty() )
    {
        offerPrice = this->ui->textEdit_offerPrice->text().replace(',','.').toDouble( &ok );
    }

    if( !ok  )
    {      
        qDebug() << "Offer-Price muss ein Zahlen-Wert sein!";

        emit saved( false );

        return;

        // throw "Offer-Price muss ein Zahlen-Wert sein!";
    }

    this->dbDataProvider->insertIntoDiscounterShopItem( shopItemId, discounterId, normalPrice, offerPrice );
    qDebug() << "Saved";

    emit saved( true );
}

void MainWindow::on_comboBox_shopItem_currentTextChanged( const QString &text )
{
    qDebug() << text;
    this->updateData();
}

void MainWindow::on_comboBox_discounter_currentTextChanged( const QString &text )
{
    qDebug() << text;
    this->updateData();
}

void MainWindow::on_pushButton_editShopItem_clicked()
{
    ShopItemDialog *dialog = new ShopItemDialog( this, "&Ändern",
                this->ui->comboBox_shopItem->currentText(),
                this->cachedShopItems[this->ui->comboBox_shopItem->currentText()] );

    QObject::connect( dialog, &ShopItemDialog::shopItemDialogOkClick,
                      this, &MainWindow::onShopItemDialogOkClicked,
                      Qt::UniqueConnection );

    dialog->exec();
}

void MainWindow::on_pushButton_editDiscounter_clicked()
{
    const uint discounterId = this->cachedDiscounters[this->ui->comboBox_discounter->currentText()];
    Discounter discounter = this->dbDataProvider->getDiscounter( discounterId );

    DiscounterDialog *dialog = new DiscounterDialog( this, "&Ändern",
                discounter.getName(),
                discounter.getLocation(),
                discounterId );

    QObject::connect( dialog, &DiscounterDialog::discounterDialogOkClick,
                      this, &MainWindow::onDiscounterDialogOkClicked,
                      Qt::UniqueConnection );

    dialog->exec();
}

void MainWindow::on_pushButton_addNewShopItem_clicked()
{
    ShopItemDialog *dialog = new ShopItemDialog( this, "&Hinzufügen", "" );

    QObject::connect( dialog, &ShopItemDialog::shopItemDialogOkClick,
                      this, &MainWindow::onShopItemDialogOkClicked,
                      Qt::UniqueConnection );

    dialog->exec();
}

void MainWindow::on_pushButton_removeShopItem_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question( this, tr( "Löschen" ),
                                     tr( "Eintrag wirklich löschen?" ),
                                    QMessageBox::Yes|QMessageBox::No );

    if( reply == QMessageBox::Yes )
    {
        qDebug() << "Yes was clicked";
        this->dbDataProvider->deleteShopItem( this->cachedShopItems[this->ui->comboBox_shopItem->currentText()] );
        this->loadShopItems();
    }
    else
    {
        qDebug() << "Yes was *not* clicked";
    }
}

void MainWindow::on_pushButton_removeDiscounter_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question( this, tr( "Löschen" ),
                                     tr( "Eintrag wirklich löschen?" ),
                                    QMessageBox::Yes|QMessageBox::No );

    if( reply == QMessageBox::Yes )
    {
        qDebug() << "Yes was clicked";
        this->dbDataProvider->deleteDiscounter( this->cachedDiscounters[this->ui->comboBox_discounter->currentText()] );
        this->loadDiscounter();
    }
    else
    {
        qDebug() << "Yes was *not* clicked";
    }
}

void MainWindow::on_actionAbout_CostimizerDBTool_triggered()
{
    QMessageBox::about( this, "About CostimizerDBTool", "A \"C++ Let's Try [Qt]\" - Community Project\nof Tutor Exilius\nhttp://twitch.tv/TutorExilius");
}

void MainWindow::onSaved( bool successful )
{
    if( successful )
    {
        QMessageBox::about( this, "Saved", "Successfully saved!" );
    }
    else
    {
        QMessageBox::about( this, "Error", "Inputs are incorrect!\nPlease type in valid numbers!" );
    }
}
