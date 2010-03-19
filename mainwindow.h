#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "project_form.h"
#include "edit_form.h"
#include "upload_form.h"
#include "test_form.h"
#include "debug_form.h"

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

private:
    Ui::MainWindow *ui;
    project_form *proj_form;
    edit_form *editor_form;
    upload_form *up_form;
    test_form *tst_form;
    debug_form *dbg_form;
};

#endif // MAINWINDOW_H
