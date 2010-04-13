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
    ui->crcmBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->add00Btn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->getDataBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->spiCheckBtn->setStyleSheet(TOOLBAR_BTN_STYLE);

    /* setup tab widgets buttons */
    setup_toolbar_buttons(ui->tabWidget->currentIndex());



    this->about = new DialogAbout(parent);
    this->compiler = new DialogCompiler(parent);
    this->dialogEditor = new DialogEditor(parent);
    this->misc = new DialogMisc(parent);

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

void MainWindow::setup_toolbar_buttons(int index)
{
    switch (index) {
    /* programming */
    case 0:
        ui->continueDebugBtn->setVisible(false);
        ui->cleaAllDebugBtn->setVisible(false);
        ui->skipAllDebugBox->setVisible(false);
        ui->compileBtn->setVisible(true);
        ui->uploadBtn->setVisible(true);
        ui->uploadBtn->setDisabled(true);
        ui->rfUploadBtn->setVisible(true);
        ui->rfUploadBtn->setDisabled(true);
        ui->crcmBtn->setVisible(false);
        ui->add00Btn->setVisible(false);
        ui->getDataBtn->setVisible(false);
        ui->spiCheckBtn->setVisible(false);
        break;
    /* debugging */
    case 1:
        ui->continueDebugBtn->setVisible(true);
        ui->cleaAllDebugBtn->setVisible(true);
        ui->skipAllDebugBox->setVisible(true);
        ui->compileBtn->setVisible(false);
        ui->uploadBtn->setVisible(false);
        ui->rfUploadBtn->setVisible(false);
        ui->crcmBtn->setVisible(false);
        ui->add00Btn->setVisible(false);
        ui->getDataBtn->setVisible(false);
        ui->spiCheckBtn->setVisible(false);
        break;
    case 2:
        ui->continueDebugBtn->setVisible(false);
        ui->cleaAllDebugBtn->setVisible(false);
        ui->skipAllDebugBox->setVisible(false);
        ui->uploadBtn->setVisible(false);
        ui->rfUploadBtn->setVisible(false);
        ui->compileBtn->setVisible(false);
        /* raw mode */
        if (ui->modeBox->currentIndex() == 1) {
            ui->crcmBtn->setVisible(true);
            ui->add00Btn->setVisible(true);
            ui->getDataBtn->setVisible(true);
            ui->spiCheckBtn->setVisible(true);
        } else {
            ui->crcmBtn->setVisible(false);
            ui->add00Btn->setVisible(false);
            ui->getDataBtn->setVisible(false);
            ui->spiCheckBtn->setVisible(false);
        }
        break;
     default:
        ui->crcmBtn->setVisible(true);
        ui->add00Btn->setVisible(true);
        ui->getDataBtn->setVisible(true);
        ui->spiCheckBtn->setVisible(true);
    }
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


void MainWindow::lang_change(void)
{

    QSettings settings("Microrisc", "misc");

    switch (settings.value("setup/lang").toInt()) {
        case 1:
            translator->load(":/new/lang/lang_cz.qm");
            break;
        case 0:
        default:
            translator->load(":/new/lang/lang_en.qm");
    }
    QApplication::installTranslator(translator);

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    setup_toolbar_buttons(index);
}

void MainWindow::on_modeBox_activated(int index)
{
    /* because toolbar buttons could be changed by
     * tab or by listBox simultaneously we use index + 1
     * to show raw terminal buttons in toolbar
     */

    if (index == 1)
        setup_toolbar_buttons(ui->tabWidget->count() + index);
}
