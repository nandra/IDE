#ifndef DIALOG_ABOUT_H
#define DIALOG_ABOUT_H

#include <QtGui/QDialog>

namespace Ui {
    class dialog_about;
}

class dialog_about : public QDialog {
    Q_OBJECT
public:
    dialog_about(QWidget *parent = 0);
    ~dialog_about();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::dialog_about *m_ui;
};

#endif // DIALOG_ABOUT_H
