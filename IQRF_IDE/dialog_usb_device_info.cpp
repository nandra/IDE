#include "dialog_usb_device_info.h"
#include "ui_dialog_usb_device_info.h"

dialog_usb_device_info::dialog_usb_device_info(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::dialog_usb_device_info)
{
    m_ui->setupUi(this);
}

dialog_usb_device_info::~dialog_usb_device_info()
{
    delete m_ui;
}

void dialog_usb_device_info::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void dialog_usb_device_info::on_pushButton_released()
{
    /* hide dialog window */
    this->setShown(false);
}
