#include "dialog_editor.h"
#include "ui_dialog_editor.h"
#include <QGroupBox>
#include <QDebug>
#include <QFileDialog>

DialogEditor::DialogEditor(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogEditor)
{
    m_ui->setupUi(this);
    this->settings_read();
}

DialogEditor::~DialogEditor()
{
    delete m_ui;
}

void DialogEditor::changeEvent(QEvent *e)
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

void DialogEditor::on_buttonBox_clicked(QAbstractButton* button)
{
    if (button->text() == "OK") {
        this->settings_write();
        accept();
    } else {
        this->setShown(false);
    }
}

void DialogEditor::settings_write()
{
    QSettings settings("Microrisc", "editor");

    settings.beginGroup("setup");
    settings.setValue("ext editor", m_ui->useExtBox->isChecked());
    settings.setValue("ext editor location", m_ui->locationLineEdit->text());
    settings.setValue("launch editor", m_ui->launchBox->isChecked());
    settings.endGroup();
}

void DialogEditor::settings_read()
{
    QSettings settings("Microrisc", "editor");

    settings.beginGroup("setup");
    m_ui->useExtBox->setChecked(settings.value("window err").toBool());
    m_ui->locationLineEdit->setText(settings.value("ext editor location").toString());
    m_ui->launchBox->setChecked(settings.value("launch editor").toBool());
    settings.endGroup();
}


void DialogEditor::on_LocationBtn_released()
{
    m_ui->locationLineEdit->setText(QFileDialog::getOpenFileName(this, tr("Editor"), "",
                                            tr("Exe file (*.exe)")));
}
