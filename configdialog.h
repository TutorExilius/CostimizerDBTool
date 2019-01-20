#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

#include "config.h"

// Forward-Declarations
class MainWindow;

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog( MainWindow *parentWindow, Config config );
    ~ConfigDialog();

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_ok_clicked();

    void on_pushButton_chooseDatabaseFile_clicked();

private:
    Ui::ConfigDialog *ui;
    MainWindow *parentWindow;
    Config config;
};

#endif // CONFIGDIALOG_H
