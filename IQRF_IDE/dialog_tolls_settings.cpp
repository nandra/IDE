#include "dialog_tolls_settings.h"
#include "ui_dialog_tolls_settings.h"
#include <QGroupBox>
#include <QDebug>
#include <QFileDialog>

dialog_tolls_settings::dialog_tolls_settings(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::dialog_tolls_settings)
{
    m_ui->setupUi(this);
    this->settings_read();
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

void dialog_tolls_settings::on_buttonBox_clicked(QAbstractButton* button)
{
    if (button->text() == "OK") {
        this->settings_write();
        accept();
    } else {
        this->setShown(false);
    }
}

void dialog_tolls_settings::settings_write()
{
    QSettings settings("Microrisc", "tools");

    settings.beginGroup("setup");
    settings.setValue("compiler location", m_ui->lineEdit->text());
    settings.setValue("compiler options", m_ui->lineEdit_2->text());
    settings.setValue("window always", m_ui->radioButton->isChecked());
    settings.setValue("window err warn", m_ui->radioButton_2->isChecked());
    settings.setValue("window err",  m_ui->radioButton_3->isChecked());
    settings.setValue("ext editor", m_ui->checkBox->isChecked());
    settings.setValue("ext editor location", m_ui->lineEdit_3->text());
    settings.setValue("launch editor", m_ui->checkBox_2->isChecked());
    settings.setValue("help", m_ui->comboBox->currentIndex());
    settings.setValue("template location", m_ui->lineEdit_4->text());
    settings.endGroup();
}

void dialog_tolls_settings::settings_read()
{
    QSettings settings("Microrisc", "tools");

    settings.beginGroup("setup");
    m_ui->lineEdit->setText(settings.value("compiler location").toString());
    m_ui->lineEdit_2->setText(settings.value("compiler options").toString());
    m_ui->radioButton->setChecked(settings.value("window always").toBool());
    m_ui->radioButton_2->setChecked(settings.value("window err warn").toBool());
    m_ui->radioButton_3->setChecked(settings.value("window err").toBool());
    m_ui->checkBox->setChecked(settings.value("window err").toBool());
    m_ui->lineEdit_3->setText(settings.value("ext editor location").toString());
    m_ui->checkBox_2->setChecked(settings.value("launch editor").toBool());
    m_ui->comboBox->setCurrentIndex(settings.value("help").toInt());
    m_ui->lineEdit_4->setText(settings.value("template location").toString());
    settings.endGroup();
}

void dialog_tolls_settings::on_pushButton_2_released()
{
    m_ui->lineEdit_2->setText(OPTIONS_DEFAULT);
}

void dialog_tolls_settings::on_pushButton_released()
{
    m_ui->lineEdit->setText(QFileDialog::getOpenFileName(this, tr("Compiler"), "",
                                            tr("Exe file (*.exe)")));
}

void dialog_tolls_settings::on_pushButton_3_released()
{
      m_ui->lineEdit_3->setText(QFileDialog::getOpenFileName(this, tr("Editor"), "",
                                            tr("Exe file (*.exe)")));
}

void dialog_tolls_settings::on_pushButton_4_released()
{
    m_ui->lineEdit_4->setText(QFileDialog::getOpenFileName(this, tr("Editor"), "",""
                                            /*tr("Exe file (*.exe)")*/));
}
