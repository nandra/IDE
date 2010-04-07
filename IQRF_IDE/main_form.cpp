#include "main_form.h"
#include "ui_main_form.h"
#include <QDebug>
#include <QMessageBox>
main_form::main_form(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::main_form)
{
    ui->setupUi(this);
    /* setup dialogs */
    this->usb_dev_info = new dialog_usb_device_info(parent);
    this->about = new dialog_about(parent);
    this->settings = new dialog_tolls_settings(parent);

    /* connections for main window widgets */
    connect(ui->actionIQRF_USB_device_info, SIGNAL(triggered()), this, SLOT(open_usb_info_dialog()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(open_about_dialog()));
    connect(ui->actionTools_settings, SIGNAL(triggered()), this, SLOT(open_tool_settings_dialog()));
}

main_form::~main_form()
{
    delete ui;
}

/* public slots */
void main_form::open_usb_info_dialog(void)
{
    this->usb_dev_info->show();
}

void main_form::open_about_dialog(void)
{
    this->about->show();
}

void main_form::open_tool_settings_dialog(void)
{
    this->settings->show();
}
