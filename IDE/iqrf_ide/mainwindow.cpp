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
#include <QAction>
#include <QSpacerItem>

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
    this->skipAllBox = new QCheckBox(tr("Skip All Debugs"));

    toolBar->addWidget(toolbar[CHECK_USB]);
    toolBar->addWidget(toolbar[RESET]);
    toolBar->addWidget(toolbar[EDIT]);


    toolBarProg->addWidget(toolbar[COMPILE]);
    toolBarProg->addWidget(toolbar[UPLOAD]);
    toolBarProg->addWidget(toolbar[RF_UPLOAD]);

    toolBarDebug->addWidget(toolbar[CONTINUE]);
    toolBarDebug->addWidget(toolbar[SKIP_ALL]);
    toolBarDebug->addWidget(skipAllBox);

    toolBarComm->addWidget(toolbar[CRCM]);
    toolBarComm->addWidget(toolbar[ADD_00]);
    toolBarComm->addWidget(toolbar[GET_DATA]);
    toolBarComm->addWidget(toolbar[SPI_CHECK]);

    this->addToolBar(toolBar);

    QLabel *st = new QLabel(tr(""));
    st->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *stText = new QLabel(tr("This is module status text"));
    stText->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    stText->setMinimumWidth(250);

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

    /* frame for status bar */
    QFrame *status_frame = new QFrame();
    status_frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QHBoxLayout *layout = new QHBoxLayout(status_frame);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    QProgressBar *bar = new QProgressBar(status_frame);
    bar->setMaximumHeight(10);
    bar->setMaximumWidth(100);

    QCheckBox *box = new QCheckBox(tr("Check Mode"), status_frame);
    box->setChecked(true);

    layout->addSpacing(30);
    layout->addWidget(bar);
    layout->addWidget(box);
    layout->addSpacing(30);

    ui->statusBar->insertWidget(5, status_frame);


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

    /* resize content of table */
    ui->tableWidget_6->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    /* watch tab handling */
    watch = new QMenu();


    act.insert(0, watch->addAction(tr("Add watch tab"), this, SLOT(add_new_watch_tab())));
    act.insert(1, watch->addAction(tr("Remove watch tab"), this, SLOT(close_tab())));
    ui->tabWidget_3->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tabWidget_3, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(right_click(const QPoint &)));

    ui->tableWidget_8->setColumnWidth(1, 70);
    ui->tableWidget_9->setColumnWidth(1, 70);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete watch;
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

    switch (index) {
    /* programming */
    case 0:
        this->addToolBar(toolBarProg);
        toolBarProg->show();
        break;
    /* debugging */
    case 1:
        this->addToolBar(toolBarDebug);
        toolBarDebug->show();
        break;
    /* communication */
    case 2:
        this->addToolBar(toolBarEmpty);
        toolBarEmpty->show();
        break;
    /* used tab count +1 for comm terminal buttons */
    case 4:
        this->addToolBar(toolBarComm);
        toolBarComm->show();
        break;
    default:
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

    if (index == 1) {
        setup_toolbar_buttons(ui->tabWidget->count() + index);
        /* disable some widgets */
        ui->checkBox_2->setVisible(false);
        ui->checkBox_3->setVisible(false);
        ui->checkBox_4->setVisible(false);
    } else {
        setup_toolbar_buttons(ui->tabWidget->count() +2);
        ui->checkBox_2->setVisible(true);
        ui->checkBox_3->setVisible(true);
        ui->checkBox_4->setVisible(true);
    }
}

void MainWindow::right_click(const QPoint &p)
{
    /* for all debug disable viewing remove */
    if (ui->tabWidget_3->currentIndex() == 0) {
        act[1]->setEnabled(false);
    } else {
        act[1]->setEnabled(true);
    }
    watch->popup(QWidget::mapToGlobal(p));
}

void MainWindow::add_new_watch_tab(void)
{
    QWidget *tab = new QWidget();
    ui->tabWidget_3->addTab(tab, "Watch"+QString::number(ui->tabWidget_3->count()));
}

void MainWindow::close_tab(void)
{
    int act_index = ui->tabWidget_3->currentIndex();
    if (act_index)
        ui->tabWidget_3->removeTab(ui->tabWidget_3->currentIndex());
}
