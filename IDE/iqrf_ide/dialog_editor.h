#ifndef DialogEditor_H
#define DialogEditor_H

#include <QtGui/QDialog>
#include <QAbstractButton>
#include <QSettings>


namespace Ui {
    class DialogEditor;
}

class DialogEditor : public QDialog {
    Q_OBJECT
public:
    DialogEditor(QWidget *parent = 0);
    ~DialogEditor();
    void settings_read(void);
    void settings_write(void);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogEditor *m_ui;
    QSettings *setup;

private slots:

    void on_LocationBtn_released();
    void on_buttonBox_clicked(QAbstractButton* button);
};

#endif // DialogEditor_H
