#ifndef DialogMisc_H
#define DialogMisc_H

#include <QtGui/QDialog>
#include <QAbstractButton>
#include <QSettings>

namespace Ui {
    class DialogMisc;
}

class DialogMisc : public QDialog {
    Q_OBJECT
public:
    DialogMisc(QWidget *parent = 0);
    ~DialogMisc();
    void settings_read(void);
    void settings_write(void);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogMisc *m_ui;
    QSettings *setup;

private slots:

    void on_languageBox_currentIndexChanged(int index);
    void on_templateBtn_released();
    void on_selectWorkspaceBtn_released();
    void on_buttonBox_clicked(QAbstractButton* button);
 signals:
    void valueChanged(int index);
};

#endif // DialogMisc_H
