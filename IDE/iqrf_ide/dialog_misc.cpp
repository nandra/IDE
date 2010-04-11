#include "dialog_misc.h"
#include "ui_dialog_misc.h"
#include <QGroupBox>
#include <QDebug>
#include <QFileDialog>
#include <QTranslator>

DialogMisc::DialogMisc(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogMisc)
{
    m_ui->setupUi(this);
    this->settings_read();
}

DialogMisc::~DialogMisc()
{
    delete m_ui;
}

void DialogMisc::changeEvent(QEvent *e)
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

void DialogMisc::on_buttonBox_clicked(QAbstractButton* button)
{
    if (button->text() == "OK") {
        this->settings_write();
        accept();
    } else {
        this->setShown(false);
    }
}

void DialogMisc::settings_write()
{
    QSettings settings("Microrisc", "misc");

    settings.beginGroup("setup");
    settings.setValue("last_wrk", m_ui->lastUsedBtn->isChecked());
    settings.setValue("fact_wrk", m_ui->factoryBtn->isChecked());
    settings.setValue("user_wrk", m_ui->userWorkspaceBtn->isChecked());
    settings.setValue("user_wrk_path", m_ui->userWorkspaceLineEdit->text());
    settings.setValue("lang", m_ui->languageBox->currentIndex());
    settings.setValue("template location", m_ui->templateLineEdit->text());
    settings.endGroup();
}

void DialogMisc::settings_read()
{
    QSettings settings("Microrisc", "misc");

    settings.beginGroup("setup");
    m_ui->lastUsedBtn->setChecked(settings.value("last_wrk").toBool());
    m_ui->factoryBtn->setChecked(settings.value("fact_wrk").toBool());
    m_ui->userWorkspaceBtn->setChecked(settings.value("user_wrk").toBool());
    m_ui->userWorkspaceLineEdit->setText(settings.value("user_wrk_path location").toString());
    m_ui->languageBox->setCurrentIndex(settings.value("lang").toInt());
    m_ui->templateLineEdit->setText(settings.value("template location").toString());
    settings.endGroup();
}


void DialogMisc::on_selectWorkspaceBtn_released()
{
   m_ui->userWorkspaceLineEdit->setText( QFileDialog::getOpenFileName(this, tr("Workspace"), "",
                                            tr("Workspace file (*.wrk)")));
}

void DialogMisc::on_templateBtn_released()
{
    m_ui->userWorkspaceLineEdit->setText( QFileDialog::getOpenFileName(this, tr("Template"), "",
                                            tr("Template file (*.tpl)")));
}

void DialogMisc::on_languageBox_currentIndexChanged(int index)
{
    emit valueChanged(index);
}

