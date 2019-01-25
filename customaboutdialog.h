#ifndef CUSTOMABOUTDIALOG_H
#define CUSTOMABOUTDIALOG_H

#include <QMessageBox>
#include <QPair>
#include <QVector>

enum class DialogSection
{
    ICON,
    TITLE,
    VERSION,
    RELEASE_DATE,
    SHORT_INFO,
    DESCRIPTION,
    RESOURCES,
    CREDITS,
    AUTHOR,
    LICENCE
};

namespace Ui {
    class CustomAboutDialog;
}

class CustomAboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomAboutDialog( QWidget *parent );
    explicit CustomAboutDialog( QWidget *parent, const QVector<QPair<DialogSection,QString>> &sectionTexts );
    virtual ~CustomAboutDialog() override;

    void initializeCustomAboutDialog( const QVector<QPair<DialogSection,QString>> &sectionTexts );

protected:
    virtual void showEvent( QShowEvent *ev ) override;

private:
    void insertLabel( const QString &text );
    void renderDialog();

    void setIcon( const QString &iconResourcePath );
    void setTitleText( const QString &title );
    void setVersionText( const QString &version );
    void setReleaseDateText( const QString &release );
    void setShortInfoText( const QString &shortInfo );
    void setDescriptionText( const QString &description );
    void setResourcesText( const QString &resources );
    void setLicenceText( const QString &licence );
    void setCredits( const QString &credits );
    void setAuthor( const QString &author );

    Ui::CustomAboutDialog *ui;

    QString title;
    QString version;
    QString release;
    QString shortInfo;
    QString description;
    QString resources;
    QString credits;
    QString author;
    QString licence;
};

#endif // CUSTOMABOUTDIALOG_H
