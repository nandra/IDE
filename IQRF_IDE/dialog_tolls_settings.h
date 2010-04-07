#ifndef DIALOG_TOLLS_SETTINGS_H
#define DIALOG_TOLLS_SETTINGS_H

#include <QtGui/QDialog>

namespace Ui {
    class dialog_tolls_settings;
}

class dialog_tolls_settings : public QDialog {
    Q_OBJECT
public:
    dialog_tolls_settings(QWidget *parent = 0);
    ~dialog_tolls_settings();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::dialog_tolls_settings *m_ui;
};

#endif // DIALOG_TOLLS_SETTINGS_H
