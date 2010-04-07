#include "dialog_tolls_settings.h"
#include "ui_dialog_tolls_settings.h"
#include <QGroupBox>

dialog_tolls_settings::dialog_tolls_settings(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::dialog_tolls_settings)
{
    m_ui->setupUi(this);

}

dialog_tolls_settings::~dialog_tolls_settings()
{
    delete m_ui;
}

void dialog_tolls_settings::changeEvent(QEvent *e)
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
