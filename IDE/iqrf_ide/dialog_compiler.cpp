#include "dialog_compiler.h"
#include "ui_dialog_compiler.h"
#include <QGroupBox>
#include <QDebug>
#include <QFileDialog>

DialogCompiler::DialogCompiler(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogCompiler)
{
    m_ui->setupUi(this);
    this->settings_read();
}

DialogCompiler::~DialogCompiler()
{
    delete m_ui;
}

void DialogCompiler::changeEvent(QEvent *e)
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

void DialogCompiler::on_buttonBox_clicked(QAbstractButton* button)
{
    if (button->text() == "OK") {
        this->settings_write();
        accept();
    } else {
        this->setShown(false);
    }
}

void DialogCompiler::settings_write()
{
    QSettings settings("Microrisc", "compiler");

    settings.beginGroup("setup");
    settings.setValue("compiler location", m_ui->locationLineEdit->text());
    settings.setValue("compiler options", m_ui->optionsLineEdit->text());
    settings.setValue("window always", m_ui->alwaysBtn->isChecked());
    settings.setValue("window err warn", m_ui->alwaysErrorBtn->isChecked());
    settings.setValue("window err",  m_ui->errorBtn->isChecked());
    settings.endGroup();
}

void DialogCompiler::settings_read()
{
    QSettings settings("Microrisc", "compiler");

    settings.beginGroup("setup");
    m_ui->locationLineEdit->setText(settings.value("compiler location").toString());
    m_ui->optionsLineEdit->setText(settings.value("compiler options").toString());
    m_ui->alwaysBtn->setChecked(settings.value("window always").toBool());
    m_ui->alwaysErrorBtn->setChecked(settings.value("window err warn").toBool());
    m_ui->errorBtn->setChecked(settings.value("window err").toBool());
    settings.endGroup();
}


void DialogCompiler::on_browseLocationBtn_released()
{
    m_ui->locationLineEdit->setText(QFileDialog::getOpenFileName(this, tr("Compiler"), "",
                                            tr("Exe file (*.exe)")));
}


void DialogCompiler::on_setOptionsBtn_released()
{
    m_ui->optionsLineEdit->setText(OPTIONS_DEFAULT);
}
