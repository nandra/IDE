#include "dialog_about.h"
#include "ui_dialog_about.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogAbout)
{
    m_ui->setupUi(this);
}

DialogAbout::~DialogAbout()
{
    delete m_ui;
}

void DialogAbout::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogAbout::on_pushButton_released()
{
    this->setShown(false);
}
