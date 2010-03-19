#include "upload_form.h"
#include "ui_upload_form.h"

upload_form::upload_form(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::upload_form)
{
    m_ui->setupUi(this);
}

upload_form::~upload_form()
{
    delete m_ui;
}

void upload_form::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
