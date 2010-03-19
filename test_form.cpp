#include "test_form.h"
#include "ui_test_form.h"

test_form::test_form(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::test_form)
{
    m_ui->setupUi(this);
}

test_form::~test_form()
{
    delete m_ui;
}

void test_form::changeEvent(QEvent *e)
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
