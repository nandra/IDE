#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QtGui/QMainWindow>
#include "dialog_usb_device_info.h"
#include "dialog_about.h"
#include "dialog_tolls_settings.h"

namespace Ui
{
    class main_form;
}

class main_form : public QMainWindow
{
    Q_OBJECT

public:
    main_form(QWidget *parent = 0);
    ~main_form();

private:
    Ui::main_form *ui;
    dialog_usb_device_info *usb_dev_info;
    dialog_about *about;
    dialog_tolls_settings *settings;
public slots:
    void open_usb_info_dialog(void);
    void open_about_dialog(void);
    void open_tool_settings_dialog(void);
};

#endif // MAIN_FORM_H
