#include "edit_form.h"
#include "ui_edit_form.h"

edit_form::edit_form(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::edit_form)
{
    m_ui->setupUi(this);
}

edit_form::~edit_form()
{
    delete m_ui;
}

void edit_form::changeEvent(QEvent *e)
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
