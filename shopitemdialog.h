#ifndef SHOPITEMDIALOG_H
#define SHOPITEMDIALOG_H

#include <QDialog>

// forward-declarations
class MainWindow;

namespace Ui {
    class ShopItemDialog;
}

class ShopItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShopItemDialog( QWidget *parent, const QString &buttonName,
                             const QString &shopItemName,
                             const uint &currentEditingShopItemId = 0 );
    ~ShopItemDialog();

private slots:
    void on_pushButton_ok_clicked();
    void onShopItemDialogOkClicked();

signals:
    void shopItemDialogOkClick( const uint &shopItemId );

private:
    Ui::ShopItemDialog *ui;
    MainWindow *mainWindow;
    const uint currentEditingShopItemId;
};

#endif // SHOPITEMDIALOG_H
