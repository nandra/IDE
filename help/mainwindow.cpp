#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDockWidget>
#include <QSplitter>
#include <QTextBrowser>
#include <QHelpIndexWidget>



class HelpBrowser:public QTextBrowser {
    public:
        HelpBrowser(QHelpEngine *help);
        QVariant loadResource(int type,const QUrl &url);
    private:
        QHelpEngine *helpEngine;
};

HelpBrowser::HelpBrowser(QHelpEngine *help)
{
    this->helpEngine = help;
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
    QHelpEngine *helpEngine = new QHelpEngine("help/help.qhc", this);
    helpEngine->setupData();
    //ui->listView->addScrollBarWidget((QWidget *)helpEngine->indexWidget(), Qt::AlignLeft);
    //helpEngine->indexWidget();

    QDockWidget *helpWindow = new QDockWidget(tr("Help"), this);
    QSplitter *helpPanel = new QSplitter(Qt::Horizontal);
    HelpBrowser *helpBrowser = new HelpBrowser(helpEngine);

    helpPanel->insertWidget(0, (QWidget *)helpEngine->indexWidget());
    helpPanel->insertWidget(1, (QWidget *)helpEngine->contentWidget());
    helpPanel->insertWidget(2, helpBrowser);
    helpPanel->setStretchFactor(1, 1);
    helpWindow->setWidget(helpPanel);
    addDockWidget(Qt::BottomDockWidgetArea, helpWindow);

    connect((QObject *)helpEngine->contentWidget(),
            SIGNAL(linkActivated(const QUrl &)),
            helpBrowser, SLOT(setSource(const QUrl &)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


