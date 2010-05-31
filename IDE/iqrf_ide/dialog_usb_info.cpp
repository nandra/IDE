#include "dialog_usb_info.h"
#include "ui_dialog_usb_info.h"

DialogUsbInfo::DialogUsbInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUsbInfo)
{
    ui->setupUi(this);
}

DialogUsbInfo::~DialogUsbInfo()
{
    delete ui;
}

void DialogUsbInfo::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogUsbInfo::on_pushButton_released()
{
    this->setShown(false);
}
