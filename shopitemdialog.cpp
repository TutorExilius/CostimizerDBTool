#include "shopitemdialog.h"
#include "ui_shopitemdialog.h"

#include "mainwindow.h"

#include <QMessageBox>

ShopItemDialog::ShopItemDialog( QWidget *parent, const QString &buttonName,
                                const QString &shopItemName,
                                const uint &currentEditingShopItemId )
: QDialog{ parent }
, ui{ new Ui::ShopItemDialog }
, mainWindow{ dynamic_cast<MainWindow*>( parent ) }
, currentEditingShopItemId{ currentEditingShopItemId }
{
    this->ui->setupUi( this );

    this->ui->pushButton_ok->setText( buttonName );
    this->ui->lineEdit_name->setText( shopItemName );

    // remove help icon
    Qt::WindowFlags flags = this->windowFlags();
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    this->setWindowFlags( flags & ~helpFlag );

    this->adjustSize();
    this->setMaximumSize( this->size() );
    this->setMinimumSize( this->size() );

    QObject::connect( this->ui->pushButton_ok, &QPushButton::clicked,
                      this, &ShopItemDialog::onShopItemDialogOkClicked,
                      Qt::UniqueConnection );
}

ShopItemDialog::~ShopItemDialog()
{
    delete ui;
}

void ShopItemDialog::on_pushButton_ok_clicked()
{
    if( this->ui->lineEdit_name->text().isEmpty() )
    {
        QMessageBox::about( this, "Missing Input", "name is empty!");
        return;
    }

    this->mainWindow->updateShopItemDBData( this->currentEditingShopItemId,
                                    this->ui->lineEdit_name->text() );
    this->close();
}

void ShopItemDialog::onShopItemDialogOkClicked()
{
    if( this->ui->lineEdit_name->text().isEmpty() )
    {
        return;
    }

    emit shopItemDialogOkClick( this->currentEditingShopItemId );
}
