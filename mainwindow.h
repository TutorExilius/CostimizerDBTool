#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "config.h"
#include "discounter.h"
#include "shopitem.h"

// forward-declarations
class DB_DataProvider;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateShopItemDBData( const uint &shopItemId, const QString &newName );
    void updateDiscounterDBData( const uint &discounterId,
                                 const QString &newName,
                                 const QString &newLocation );

public slots:
    void onShopItemDialogOkClicked( const uint &shopItemId );
    void onDiscounterDialogOkClicked( const uint &discounterId );

private slots:
    void on_action_About_Qt_triggered();
    void on_action_Close_triggered();

    void on_pushButton_addNewDiscounter_clicked();

    void on_pushButton_save_clicked();

    void on_comboBox_shopItem_currentTextChanged(const QString &arg1);

    void on_comboBox_discounter_currentTextChanged(const QString &arg1);

    void on_pushButton_editShopItem_clicked();

    void on_pushButton_editDiscounter_clicked();

    void on_pushButton_addNewShopItem_clicked();

    void on_pushButton_removeShopItem_clicked();

    void on_pushButton_removeDiscounter_clicked();

private:
    void addNewDiscounter( const QString &name, const QString &location );
    QList<ShopItem> getShopItems() const;
    void loadShopItems();
    void loadDiscounter();
    void updateData();
    void updateSaveButtonView();

    Ui::MainWindow *ui;
    DB_DataProvider *dbDataProvider;
    Config config;

    QMap<QString, uint> cachedDiscounters;
    QMap<QString, uint> cachedShopItems;
};

#endif // MAINWINDOW_H
