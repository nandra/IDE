#ifndef DIALOG_USB_INFO_H
#define DIALOG_USB_INFO_H

#include <QDialog>

namespace Ui {
    class DialogUsbInfo;
}

class DialogUsbInfo : public QDialog {
    Q_OBJECT
public:
    DialogUsbInfo(QWidget *parent = 0);
    ~DialogUsbInfo();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogUsbInfo *ui;

private slots:
    void on_pushButton_released();
};

#endif // DIALOG_USB_INFO_H
