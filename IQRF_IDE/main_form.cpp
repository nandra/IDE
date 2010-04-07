#include "main_form.h"
#include "ui_main_form.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

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
    connect(ui->actionIQRF_home_page, SIGNAL(triggered()), this, SLOT(open_home_url()));
    connect(ui->actionIQRF_support, SIGNAL(triggered()), this, SLOT(open_support_url()));

    this->settings_read();
}

main_form::~main_form()
{
    this->settings_write();
    delete ui;
}

/* public functions */
/* write form settings */
void main_form::settings_write()
{
    QSettings settings("Microrisc", "form");

    settings.beginGroup("setup form");
    settings.setValue("updates", ui->actionCheck_for_IQRF_IDE_updates->isChecked());
    settings.setValue("news", ui->actionCheck_for_IQRF_news->isChecked());
    settings.setValue("upload beep", ui->actionBeep_on_upload->isChecked());
    settings.setValue("debug beep", ui->actionBeep_on_debug->isChecked());
    settings.endGroup();
}

/* read for settings */
void main_form::settings_read()
{
    QSettings settings("Microrisc", "form");

    settings.beginGroup("setup form");
    ui->actionCheck_for_IQRF_IDE_updates->setChecked(settings.value("updates").toBool());
    ui->actionCheck_for_IQRF_news->setChecked(settings.value("news").toBool());
    ui->actionBeep_on_upload->setChecked(settings.value("upload beep").toBool());
    ui->actionBeep_on_debug->setChecked(settings.value("debug beep").toBool());
    settings.endGroup();
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

bool open_url(const QUrl & url)
{
    return QDesktopServices::openUrl(url);
}

void main_form::open_home_url(void)
{
    open_url(QUrl::fromEncoded("http://www.microrisc.com"));
}

void main_form::open_support_url(void)
{
    open_url(QUrl::fromEncoded("http://www.iqrf.com/weben/index.php?sekce=support"));
}


