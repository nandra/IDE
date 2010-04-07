#include "dialog_about.h"
#include "ui_dialog_about.h"

dialog_about::dialog_about(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::dialog_about)
{
    m_ui->setupUi(this);
    m_ui->label->setText("<h2>IQRF IDE</h2>");
}

dialog_about::~dialog_about()
{
    delete m_ui;
}

void dialog_about::changeEvent(QEvent *e)
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
