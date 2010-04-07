#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDockWidget>
#include <QSplitter>
#include <QTextBrowser>
#include <QHelpIndexWidget>
#include <QHelpSearchEngine>
#include <QLabel>
#include <QLineEdit>
class HelpBrowser:public QTextBrowser {
    public:
        HelpBrowser( QHelpEngine *help);
        ~HelpBrowser();
        QVariant loadResource(int type,const QUrl &url);
    private:
        QHelpEngine *helpEngine;
};

HelpBrowser::HelpBrowser(QHelpEngine *help)
{
    this->helpEngine = help;
}

HelpBrowser::~HelpBrowser()
{

}

 QVariant HelpBrowser::loadResource(int type,
                                       const QUrl &url)
    {
        if (url.scheme() == "qthelp")
            return QVariant(helpEngine->fileData(url));
        else
            return QTextBrowser::loadResource(type, url);
    }


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHelpEngine *helpEngine = new QHelpEngine("./help_www/help.qhc", this);
    helpEngine->setupData();
    QHelpSearchEngine *search = new QHelpSearchEngine(helpEngine, this);

    QDockWidget *helpWindow = new QDockWidget(tr("Help"), this);
    QSplitter *helpPanel = new QSplitter(Qt::Horizontal);
    HelpBrowser *helpBrowser = new HelpBrowser(helpEngine);

    helpPanel->insertWidget(0, (QWidget *)helpEngine->indexWidget());
    //helpPanel->insertWidget(0, (QWidget *)search->queryWidget());
    helpPanel->insertWidget(1, (QWidget *)helpEngine->contentWidget());
    helpPanel->insertWidget(2, helpBrowser);
    helpPanel->setStretchFactor(1, 1);
    helpWindow->setWidget(helpPanel);
    addDockWidget(Qt::BottomDockWidgetArea, helpWindow);

    connect((QObject *)helpEngine->contentWidget(),
            SIGNAL(linkActivated(const QUrl &)),
            helpBrowser, SLOT(setSource(const QUrl &)));
    connect((QObject *)helpEngine->indexWidget(), SIGNAL(linkActivated(QUrl,QString)),
            helpBrowser, SLOT(setSource(const QUrl &)));
    QLabel *lbl = new QLabel("Text", parent);
    QLineEdit *lbl1 = new QLineEdit(parent);
    lbl1->setText("Text");
    lbl1->setReadOnly(true);
    QSplitter *splitter = new QSplitter(parent);
    splitter->addWidget(lbl);
    splitter->addWidget(lbl1);
    ui->statusBar->addWidget(splitter);
}

MainWindow::~MainWindow()
{
    delete ui;
}


