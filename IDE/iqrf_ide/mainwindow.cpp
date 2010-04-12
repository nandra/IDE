#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <QDebug>
#include <QStyle>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    this->translator = new QTranslator(parent);
    QSettings settings("Microrisc", "misc");

    switch (settings.value("setup/lang").toInt()) {
    case 1:
        qDebug() << "Loading cz lang file:" << translator->load(":/new/lang/lang_cz.qm");
        break;
    case 0:
    default:
        qDebug() << "Loading en lang file:" << translator->load(":/new/lang/lang_en.qm");
        break;
    }
    QApplication::installTranslator(translator);

    /* style setup for mainwindow */
    ui->checkUSBBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->resetBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->editBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->compileBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->uploadBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->rfUploadBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->continueDebugBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->cleaAllDebugBtn->setStyleSheet(TOOLBAR_BTN_STYLE);

    /* setup tab widgets */
    //this->programming = new FormProgramming(parent);
    //ui->tabWidget->insertTab(0, programming,tr("Programming"));


    this->about = new DialogAbout(parent);
    this->compiler = new DialogCompiler(parent);
    this->dialogEditor = new DialogEditor(parent);
    this->misc = new DialogMisc(parent);
    connect(misc, SIGNAL(valueChanged(int)), this,SLOT(lang_changed(int)));
    connect(misc, SIGNAL(finished(int)), this,SLOT(lang_change()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
}


/* public slots */

/* open usb device info dialog */
void MainWindow::on_actionShow_IQRF_USB_Device_info_triggered()
{
    QMessageBox::about(this, tr("USB device info"),
                               tr("Device type:")+ "CK-USB-02\n"+\
                                tr("FW Version:")+ "2.01\n"+\
                                           tr("ID:")+ "1234657");
}
/* open nabout menu dialog */
void MainWindow::on_actionAbout_2_triggered()
{
    about->show();
}


/* open homepage */
void MainWindow::on_actionIQRF_Home_page_triggered()
{
    QDesktopServices::openUrl(QUrl::fromEncoded("http://www.microrisc.com"));
}

/* open support homepage */
void MainWindow::on_actionIQRF_Support_triggered()
{
    QDesktopServices::openUrl(QUrl::fromEncoded("http://www.iqrf.com/weben/index.php?sekce=support"));
}

void MainWindow::on_actionCompiler_triggered()
{
    compiler->show();
}

void MainWindow::on_actionEditor_triggered()
{
    dialogEditor->show();
}

void MainWindow::on_actionMiscellaneous_triggered()
{
    misc->show();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

/*
 * Setting of language is little bit tricky
 * when language is changed then signal is
 * emitted from misc dialog. value is remembered
 * and when dialog is closed then language is changed
 * otherwise it makes some troubles (circular dependency)
*/
void MainWindow::lang_changed(int index)
{
    this->language = index;
}

void MainWindow::lang_change(void)
{

    QSettings settings("Microrisc", "misc");

    int old_value = settings.value("setup/lang").toInt();

    if (old_value != this->language + 1) {

        switch (this->language) {
        case 1:
            translator->load(":/new/lang/lang_cz.qm");
            break;
        case 0:
        default:
            translator->load(":/new/lang/lang_en.qm");
        }
        QApplication::installTranslator(translator);
    }
}
