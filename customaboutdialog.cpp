#include "customaboutdialog.h"
#include "ui_customaboutdialog.h"

#include <QDebug>
#include <QDesktopServices>
#include <QScrollBar>

CustomAboutDialog::CustomAboutDialog( QWidget *parent )
: QDialog{ parent }
, ui{ new Ui::CustomAboutDialog }
{
    this->ui->setupUi( this );

    Qt::WindowFlags flags = windowFlags();

    // remove Help Button of window
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    flags = flags & ( ~helpFlag );
    this->setWindowFlags( flags );

    this->ui->pushButton_ok->setFocus();
}

CustomAboutDialog::CustomAboutDialog( QWidget *parent, const QVector<QPair<DialogSection,QString>> &sectionTexts )
: CustomAboutDialog{ parent }
{   
    this->initializeCustomAboutDialog( sectionTexts );
}

CustomAboutDialog::~CustomAboutDialog()
{
    delete ui;
}

void CustomAboutDialog::setIcon( const QString &iconResourcePath )
{
    QPixmap image( iconResourcePath );
    this->ui->label_appIconPlaceholder->setPixmap( image );
}

void CustomAboutDialog::initializeCustomAboutDialog( const QVector<QPair<DialogSection,QString>> &sectionTexts )
{
    for( const auto &pair : sectionTexts )
    {
        const DialogSection key = pair.first;
        const QString value = pair.second;

        switch( key )
        {
        case DialogSection::ICON:
            this->setIcon( value );
            break;

        case DialogSection::TITLE:
            this->setTitleText( value );
            break;

        case DialogSection::VERSION:
            this->setVersionText( value );
            break;

        case DialogSection::RELEASE_DATE:
            this->setReleaseDateText( value );
            break;

        case DialogSection::SHORT_INFO:
            this->setShortInfoText( value );
            break;

        case DialogSection::DESCRIPTION:
            this->setDescriptionText( value );
            break;

        case DialogSection::RESOURCES:
            this->setResourcesText( value );
            break;

        case DialogSection::CREDITS:
            this->setCredits( value );
            break;

        case DialogSection::AUTHOR:
            this->setAuthor( value );
            break;

        case DialogSection::LICENCE:
            this->setLicenceText( value );
            break;

        default:
            qDebug() << "[CustomAboutDialog::initializeCustomAboutDialog()] - "
                        "switch default-case should not happend.";
        }
    }

    this->renderDialog();
}

void CustomAboutDialog::setTitleText( const QString &title )
{
    this->title = "<b>" + title + "<b>";

    this->setWindowTitle( title );
}

void CustomAboutDialog::setVersionText( const QString &version )
{
   this->version = version;
}

void CustomAboutDialog::setReleaseDateText( const QString &release )
{
    this->release = release;
}

void CustomAboutDialog::setShortInfoText( const QString &shortInfo )
{
    this->shortInfo = shortInfo;
}

void CustomAboutDialog::setDescriptionText( const QString &description )
{
    this->description = description;
}

void CustomAboutDialog::setResourcesText( const QString &resources )
{
    this->resources = resources;
}

void CustomAboutDialog::setLicenceText( const QString &licence )
{
    this->licence = licence;
}

void CustomAboutDialog::setCredits( const QString &credits )
{
    this->credits = credits;
}

void CustomAboutDialog::setAuthor( const QString &author )
{
    this->author = author;
}

void CustomAboutDialog::insertLabel( const QString &text )
{
    QLabel *label = new QLabel;
    label->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Expanding );
    label->setText( text );
    label->setStyleSheet( "margin: 0px; padding: 0px;" );
    label->setWordWrap( true );
    label->setOpenExternalLinks( true );

    this->ui->verticalLayout_labels->addWidget( label );
}

void CustomAboutDialog::showEvent( QShowEvent *ev )
{
    QDialog::showEvent( ev );

  //  this->adjustSize();
  //  this->setFixedHeight( this->sizeHint().height() );
}

void CustomAboutDialog::renderDialog()
{
    // 1st
    if( !this->title.isEmpty() )
    {
        this->insertLabel( this->title );
        this->insertLabel( "" );
    }

    // 2nd
    if( !this->version.isEmpty() && !this->release.isEmpty() )
    {
        this->insertLabel( this->version );
        this->insertLabel( this->release );
        this->insertLabel( "" );
    }

    // 3th
    if( !this->shortInfo.isEmpty() )
    {
        this->insertLabel( this->shortInfo );
        this->insertLabel( "" );
    }

    // 4th
    if( !this->description.isEmpty() )
    {
        this->insertLabel( this->description );
        this->insertLabel( "" );
    }

    // 5th
    if( !this->resources.isEmpty() )
    {
        this->insertLabel( this->resources );
        this->insertLabel( "" );
    }

    // 6th
    if( !this->credits.isEmpty() )
    {
        this->insertLabel( this->credits );
        this->insertLabel( "" );
    }

    // 7th
    if( !this->author.isEmpty() )
    {
        this->insertLabel( "<b>Author<b>" );
        this->insertLabel( this->author );
        this->insertLabel( "" );
    }

    // 8th
    if( !this->licence.isEmpty() )
    {
        this->insertLabel( "<b>Licence<b>" );
        this->insertLabel( this->licence );
    }
}
