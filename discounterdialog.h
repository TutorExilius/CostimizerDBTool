#ifndef DISCOUNTERDIALOG_H
#define DISCOUNTERDIALOG_H

#include <QDialog>

// forward-declarations
class MainWindow;

namespace Ui {
    class DiscounterDialog;
}

class DiscounterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DiscounterDialog( QWidget *parent, const QString &buttonName,
                             const QString &discounterName,
                             const QString &location,
                             const uint &currentEditingDiscounterId = 0 );
    ~DiscounterDialog();

private slots:
    void on_pushButton_ok_clicked();
    void onDiscounterDialogOkClicked();

signals:
    void discounterDialogOkClick( const uint &discounterId );

private:
    Ui::DiscounterDialog *ui;
    MainWindow *mainWindow;
    const uint currentEditingDiscounterId;
};

#endif // DISCOUNTERDIALOG_H
