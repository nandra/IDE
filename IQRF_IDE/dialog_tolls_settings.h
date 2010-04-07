#ifndef DIALOG_TOLLS_SETTINGS_H
#define DIALOG_TOLLS_SETTINGS_H

#include <QtGui/QDialog>
#include <QAbstractButton>
#include <QSettings>

#define OPTIONS_DEFAULT "-a -bu -Q -Vn -cif"

namespace Ui {
    class dialog_tolls_settings;
}

class dialog_tolls_settings : public QDialog {
    Q_OBJECT
public:
    dialog_tolls_settings(QWidget *parent = 0);
    ~dialog_tolls_settings();
    void settings_read(void);
    void settings_write(void);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::dialog_tolls_settings *m_ui;
    QSettings *setup;

private slots:
    void on_pushButton_4_released();
    void on_pushButton_3_released();
    void on_pushButton_released();
    void on_pushButton_2_released();
    void on_buttonBox_clicked(QAbstractButton* button);
};

#endif // DIALOG_TOLLS_SETTINGS_H
