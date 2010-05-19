#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "dialog_about.h"
#include "dialog_compiler.h"
#include "dialog_editor.h"
#include "dialog_misc.h"
#include "dialog_usb_info.h"
#include <QTranslator>
#include "style.h"
#include <QList>
#include <QToolBar>
#include <QCheckBox>
#include <QLabel>

enum toolbarBtns{
    CHECK_USB,
    RESET,
    EDIT,
    COMPILE,
    UPLOAD,
    RF_UPLOAD,
    CONTINUE,
    SKIP_ALL,
    CRCM,
    ADD_00,
    GET_DATA,
    SPI_CHECK,
    BTN_MAX
};

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void changeEvent(QEvent *event);
    void setup_toolbar_buttons(int index);
    QPushButton *create_toolbar_button(const QString &name, bool disabled = false);

private:
    Ui::MainWindow *ui;
    DialogAbout *about;
    DialogCompiler *compiler;
    DialogEditor *dialogEditor;
    DialogMisc *misc;
    DialogUsbInfo *usbInfo;
    QTranslator *translator;
    QList<QPushButton *> toolbar;
    QToolBar *toolBar, *toolBarProg, *toolBarDebug, *toolBarComm, *toolBarEmpty, *toolBarMid;
    QLabel *btnEmpty;
    QCheckBox *skipAllBox;
    QMenu *watch;

private slots:
    void on_modeBox_activated(int index);
    void on_tabWidget_currentChanged(int index);
    void on_actionExit_triggered();
    void on_actionMiscellaneous_triggered();
    void on_actionEditor_triggered();
    void on_actionCompiler_triggered();
    void on_actionIQRF_Support_triggered();
    void on_actionIQRF_Home_page_triggered();
    void on_actionAbout_2_triggered();
    void on_actionShow_IQRF_USB_Device_info_triggered();
    void lang_change(void);
    void right_click(const QPoint &p);
    void add_new_watch_tab(void);
    void close_tab(void);
};

#endif // MAINWINDOW_H
