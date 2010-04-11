#ifndef DialogCompiler_H
#define DialogCompiler_H

#include <QtGui/QDialog>
#include <QAbstractButton>
#include <QSettings>

#define OPTIONS_DEFAULT "-a -bu -Q -Vn -cif"

namespace Ui {
    class DialogCompiler;
}

class DialogCompiler : public QDialog {
    Q_OBJECT
public:
    DialogCompiler(QWidget *parent = 0);
    ~DialogCompiler();
    void settings_read(void);
    void settings_write(void);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogCompiler *m_ui;
    QSettings *setup;

private slots:
    void on_setOptionsBtn_released();
    void on_browseLocationBtn_released();
    void on_buttonBox_clicked(QAbstractButton* button);
};

#endif // DialogCompiler_H
