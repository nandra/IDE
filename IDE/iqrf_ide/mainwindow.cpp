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
    /* set window title depending on version in makefile */
    this->window()->setWindowTitle("IQRF IDE v3.00d");

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

    toolbar.insert(COMPILE, create_toolbar_button(tr("Compile")));
    toolbar.insert(UPLOAD, create_toolbar_button(tr("Upload")));
    toolbar.insert(RF_UPLOAD, create_toolbar_button(tr("RF Upload")));
    toolbar.insert(CONTINUE, create_toolbar_button(tr("Continue")));
    toolbar.insert(SKIP_ALL, create_toolbar_button(tr("Skip All")));
    toolbar.insert(CRCM, create_toolbar_button(tr("CRCM")));
    toolbar.insert(ADD_00, create_toolbar_button(tr("Add.00.")));
    toolbar.insert(GET_DATA, create_toolbar_button(tr("Get Data")));
    toolbar.insert(SPI_CHECK, create_toolbar_button(tr("SPI Check")));


    /* style setup for mainwindow */
    ui->checkUSBBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->resetBtn->setStyleSheet(TOOLBAR_BTN_STYLE);
    ui->editBtn->setStyleSheet(TOOLBAR_BTN_STYLE);

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
        ui->horizontalLayout_3->addWidget(toolbar[COMPILE]);
        ui->horizontalLayout_3->addWidget(toolbar[UPLOAD]);
        ui->horizontalLayout_3->addWidget(toolbar[RF_UPLOAD]);
        break;
    /* debugging */
    case 1:
        ui->horizontalLayout_3->removeWidget(toolbar[COMPILE]);
        toolbar[COMPILE]->setVisible(false);
        ui->horizontalLayout_3->removeWidget(toolbar[UPLOAD]);
        toolbar[UPLOAD]->setVisible(false);
        ui->horizontalLayout_3->removeWidget(toolbar[RF_UPLOAD]);
        toolbar[RF_UPLOAD]->setVisible(false);
        ui->horizontalLayout_3->addWidget(toolbar[CONTINUE]);
        ui->horizontalLayout_3->addWidget(toolbar[SKIP_ALL]);
        break;
    case 2:
        /* visible nothing */
        break;
     default:
        ui->horizontalLayout_3->addWidget(toolbar[CRCM]);
        ui->horizontalLayout_3->addWidget(toolbar[ADD_00]);
        ui->horizontalLayout_3->addWidget(toolbar[GET_DATA]);
        ui->horizontalLayout_3->addWidget(toolbar[SPI_CHECK]);
        break;
    }
}

QPushButton *MainWindow::create_toolbar_button(const QString &name, bool disabled)
{
    QPushButton *btn = new QPushButton(name);
    btn->setFlat(true);
    btn->setStyleSheet(TOOLBAR_BTN_STYLE);
    btn->setDisabled(disabled);
    return btn;
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
