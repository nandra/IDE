#ifndef DIALOG_USB_DEVICE_INFO_H
#define DIALOG_USB_DEVICE_INFO_H

#include <QtGui/QDialog>

namespace Ui {
    class dialog_usb_device_info;
}

class dialog_usb_device_info : public QDialog {
    Q_OBJECT
public:
    dialog_usb_device_info(QWidget *parent = 0);
    ~dialog_usb_device_info();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::dialog_usb_device_info *m_ui;

private slots:
    void on_pushButton_released();
};

#endif // DIALOG_USB_DEVICE_INFO_H
