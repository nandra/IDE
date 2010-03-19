#include "debug_form.h"
#include "ui_debug_form.h"

debug_form::debug_form(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::debug_form)
{
    m_ui->setupUi(this);
}

debug_form::~debug_form()
{
    delete m_ui;
}

void debug_form::changeEvent(QEvent *e)
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
