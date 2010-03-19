#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    proj_form = new project_form();
    editor_form = new edit_form();
    up_form = new upload_form();
    tst_form = new test_form();
    dbg_form = new debug_form();

    /* add tabs manually */
    ui->tabWidget->removeTab(0);
    ui->tabWidget->addTab(proj_form,tr("Project"));
    ui->tabWidget->addTab(editor_form,tr("Editor"));
    ui->tabWidget->addTab(up_form,tr("Upload"));
    ui->tabWidget->addTab(tst_form,tr("Testing"));
    ui->tabWidget->addTab(dbg_form,tr("Debug"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
