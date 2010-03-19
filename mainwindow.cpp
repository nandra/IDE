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
    /*ui->tabWidget->removeTab(0);
    ui->tabWidget->addTab(proj_form,tr("Project"));
    ui->tabWidget->addTab(editor_form,tr("Editor"));
    ui->tabWidget->addTab(up_form,tr("Upload"));
    ui->tabWidget->addTab(tst_form,tr("Testing"));
    ui->tabWidget->addTab(dbg_form,tr("Debug"));*/
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(0, proj_form);
    ui->stackedWidget->setCurrentWidget(proj_form);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_toolButton_released()
{
     ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(0, proj_form);
    ui->stackedWidget->setCurrentWidget(proj_form);
}

void MainWindow::on_toolButton_5_released()
{
     ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(0, dbg_form);
    ui->stackedWidget->setCurrentWidget(dbg_form);
}

void MainWindow::on_toolButton_4_released()
{
     ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(0, tst_form);
    ui->stackedWidget->setCurrentWidget(tst_form);
}

void MainWindow::on_toolButton_3_released()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(0, up_form);
    ui->stackedWidget->setCurrentWidget(up_form);
}

void MainWindow::on_toolButton_2_released()
{
     ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(0, editor_form);
    ui->stackedWidget->setCurrentWidget(editor_form);
}

void MainWindow::on_toolButton_6_released()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(0, proj_form);
    ui->stackedWidget->setCurrentWidget(proj_form);
}
