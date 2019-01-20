#include "discounterdialog.h"
#include "ui_discounterdialog.h"

#include "mainwindow.h"

#include <QMessageBox>

DiscounterDialog::DiscounterDialog( QWidget *parent, const QString &buttonName,
                                const QString &discounterName,
                                const QString &location,
                                const uint &currentEditingDiscounterId )
: QDialog{ parent }
, ui{ new Ui::DiscounterDialog }
, mainWindow{ dynamic_cast<MainWindow*>( parent ) }
, currentEditingDiscounterId{ currentEditingDiscounterId }
{
    this->ui->setupUi( this );

    this->ui->pushButton_ok->setText( buttonName );
    this->ui->lineEdit_name->setText( discounterName );
    this->ui->lineEdit_location->setText( location );

    // remove help icon
    Qt::WindowFlags flags = this->windowFlags();
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    this->setWindowFlags( flags & ~helpFlag );

    this->adjustSize();
    this->setMaximumSize( this->size() );
    this->setMinimumSize( this->size() );


    QObject::connect( this->ui->pushButton_ok, &QPushButton::clicked,
                      this, &DiscounterDialog::onDiscounterDialogOkClicked,
                      Qt::UniqueConnection );
}

DiscounterDialog::~DiscounterDialog()
{
    delete ui;
}

void DiscounterDialog::on_pushButton_ok_clicked()
{
    if( this->ui->lineEdit_name->text().isEmpty() ||
        this->ui->lineEdit_location->text().isEmpty() )
    {
        QMessageBox::about( this, "Missing Input", "One of your inputs is empty!");

        return;
    }

    this->mainWindow->updateDiscounterDBData( this->currentEditingDiscounterId,
                                    this->ui->lineEdit_name->text(),
                                    this->ui->lineEdit_location->text() );
    this->close();
}

void DiscounterDialog::onDiscounterDialogOkClicked()
{
    emit discounterDialogOkClick( this->currentEditingDiscounterId );
}
