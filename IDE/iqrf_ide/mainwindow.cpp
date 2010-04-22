#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <QDebug>
#include <QStyle>
#include <QPushButton>
#include <QProgressBar>
#include <QCheckBox>

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

    toolBar = new QToolBar(parent);
    toolBar->setMovable(false);
    toolBar->setStyleSheet("QToolBar {background-color: qlineargradient(spread:pad, x1:1, y1:1, "\
                           "x2:1, y2:0, stop:0 rgba(40, 130, 240, 255), stop:1 rgba(255, 255, 255, 255));}");

    toolBarProg = new QToolBar(parent);
    toolBarProg->setMovable(false);
    toolBarProg->setStyleSheet("QToolBar {background-color: qlineargradient(spread:pad, x1:1, y1:1, "\
                            "x2:1, y2:0, stop:0 rgba(93, 153, 206, 255), stop:1 rgba(255, 255, 255, 255));}");

    toolBarDebug = new QToolBar(parent);
    toolBarDebug->setMovable(false);
    toolBarDebug->setStyleSheet("QToolBar {background-color: qlineargradient(spread:pad, x1:1, y1:1, "\
                            "x2:1, y2:0, stop:0 rgba(93, 153, 206, 255), stop:1 rgba(255, 255, 255, 255));}");

    toolBarComm = new QToolBar(parent);
    toolBarComm->setMovable(false);
    toolBarComm->setStyleSheet("QToolBar {background-color: qlineargradient(spread:pad, x1:1, y1:1, "\
                            "x2:1, y2:0, stop:0 rgba(93, 153, 206, 255), stop:1 rgba(255, 255, 255, 255));}");

    toolBarEmpty = new QToolBar(parent);
    toolBarEmpty->setMovable(false);
    toolBarEmpty->setStyleSheet("QToolBar {background-color: qlineargradient(spread:pad, x1:1, y1:1, "\
                            "x2:1, y2:0, stop:0 rgba(93, 153, 206, 255), stop:1 rgba(255, 255, 255, 255));}");

    toolBarMid = new QToolBar(parent);
    toolBarMid->setMovable(false);

    toolbar.insert(CHECK_USB, create_toolbar_button(tr("Check USB Device")));
    toolbar.insert(RESET, create_toolbar_button(tr("Reset TR Module")));
    toolbar.insert(EDIT, create_toolbar_button(tr("Edit")));
    toolbar.insert(COMPILE, create_toolbar_button(tr("Compile")));
    toolbar.insert(UPLOAD, create_toolbar_button(tr("Upload"), true));
    toolbar.insert(RF_UPLOAD, create_toolbar_button(tr("RF Upload"), true));
    toolbar.insert(CONTINUE, create_toolbar_button(tr("Continue"), true));
    toolbar.insert(SKIP_ALL, create_toolbar_button(tr("Clear All")));
    toolbar.insert(CRCM, create_toolbar_button(tr("CRCM")));
    toolbar.insert(ADD_00, create_toolbar_button(tr("Add.00.")));
    toolbar.insert(GET_DATA, create_toolbar_button(tr("Get Data")));
    toolbar.insert(SPI_CHECK, create_toolbar_button(tr("SPI Check")));


    /* style setup for mainwindow */

    toolBar->addWidget(toolbar[CHECK_USB]);
    toolBar->addWidget(toolbar[RESET]);
    toolBar->addWidget(toolbar[EDIT]);


    toolBarProg->addWidget(toolbar[COMPILE]);
    toolBarProg->addWidget(toolbar[UPLOAD]);
    toolBarProg->addWidget(toolbar[RF_UPLOAD]);

    toolBarDebug->addWidget(toolbar[CONTINUE]);
    toolBarDebug->addWidget(toolbar[SKIP_ALL]);

    toolBarComm->addWidget(toolbar[CRCM]);
    toolBarComm->addWidget(toolbar[ADD_00]);
    toolBarComm->addWidget(toolbar[GET_DATA]);
    toolBarComm->addWidget(toolbar[SPI_CHECK]);

    QWidget *w = new QWidget(this->toolBarMid);
    QHBoxLayout *hbox = new QHBoxLayout(w);
    this->skipAllBox = new QCheckBox(tr("Skip all"));
    hbox->addSpacing(20);
    hbox->addWidget(skipAllBox);
    skipAllBox->setVisible(false);
    hbox->addSpacing(20);

    w->setLayout(hbox);
    toolBarMid->addWidget(w);

    this->addToolBar(toolBar);
    this->addToolBar(toolBarMid);

    QLabel *st = new QLabel(tr(""));
    st->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *stText = new QLabel(tr("This is module status text"));
    stText->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    stText->setMinimumWidth(300);

    QLabel *moduleType = new QLabel(tr("TR-52B"));
    moduleType->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *os = new QLabel(tr("OS 2.11 (0878)"));
    os->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *id = new QLabel(tr("ID:10000567"));
    id->setFrameStyle(QFrame::Panel | QFrame::Sunken);


    ui->statusBar->insertWidget(0, st);
    ui->statusBar->insertWidget(1, stText);
    ui->statusBar->insertWidget(2, moduleType);
    ui->statusBar->insertWidget(3, os);
    ui->statusBar->insertWidget(4, id);

    QProgressBar *bar = new QProgressBar(parent);
    bar->setMaximumHeight(10);
    bar->setMaximumWidth(100);
    ui->statusBar->addPermanentWidget(bar);


    QCheckBox *box = new QCheckBox(tr("Check mode"));
    box->setChecked(true);
    ui->statusBar->addPermanentWidget(box);


    /* setup tab widgets buttons */
    setup_toolbar_buttons(ui->tabWidget->currentIndex());

    this->about = new DialogAbout(parent);
    this->compiler = new DialogCompiler(parent);
    this->dialogEditor = new DialogEditor(parent);
    this->misc = new DialogMisc(parent);
    this->usbInfo = new DialogUsbInfo(parent);
    connect(misc, SIGNAL(finished(int)), this,SLOT(lang_change()));

    ui->trModuleBox->addItem(tr("TR-11A"));
    ui->trModuleBox->addItem(tr("TR-21A"));
    ui->trModuleBox->addItem(tr("TR-31B"));
    ui->trModuleBox->addItem(tr("TR-32B"));
    ui->trModuleBox->addItem(tr("TR-52B"));
    ui->trModuleBox->addItem(tr("TR-53B"));
    ui->trModuleBox->setCurrentIndex(4);

    /*FIXME!!! only for presentation remove */
    ui->checkBox11->setDisabled(true);
    ui->checkBox12->setDisabled(true);
    ui->checkBox2->setDisabled(true);
    ui->checkBox3->setDisabled(true);
    ui->checkBox21->setDisabled(true);
    ui->checkBox22->setDisabled(true);
    ui->checkBox31->setDisabled(true);
    ui->checkBox32->setDisabled(true);
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
    this->removeToolBar(toolBarProg);
    this->removeToolBar(toolBarDebug);
    this->removeToolBar(toolBarComm);
    this->removeToolBar(toolBarEmpty);
    skipAllBox->setVisible(false);
    switch (index) {
    /* programming */
    case 0:
        this->addToolBar(toolBarProg);
        toolBarProg->show();
        break;
    /* debugging */
    case 1:
        skipAllBox->setVisible(true);
        this->addToolBar(toolBarDebug);
        toolBarDebug->show();
        break;
    /* communication */
    case 2:
        this->addToolBar(toolBarEmpty);
        toolBarEmpty->show();
        break;
    /* used tab count +1 for comm terminal buttons */
    default:
        this->addToolBar(toolBarComm);
        toolBarComm->show();
        break;
    }
    /* add permanent toolbars */

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
    usbInfo->show();
}

/* open nabout menu dialog */
void MainWindow::on_actionAbout_2_triggered()
{
    about->show();
}


/* open homepage */
void MainWindow::on_actionIQRF_Home_page_triggered()
{
    QDesktopServices::openUrl(QUrl::fromEncoded("http://www.iqrf.org"));
}

/* open support homepage */
void MainWindow::on_actionIQRF_Support_triggered()
{
    QDesktopServices::openUrl(QUrl::fromEncoded("http://www.iq-esupport.com"));
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
