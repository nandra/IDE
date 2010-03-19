#include "project_form.h"
#include "ui_project_form.h"

project_form::project_form(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::project_form)
{
    m_ui->setupUi(this);
}

project_form::~project_form()
{
    delete m_ui;
}

void project_form::changeEvent(QEvent *e)
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
