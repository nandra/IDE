#ifndef EDIT_FORM_H
#define EDIT_FORM_H

#include <QtGui/QWidget>

namespace Ui {
    class edit_form;
}

class edit_form : public QWidget {
    Q_OBJECT
public:
    edit_form(QWidget *parent = 0);
    ~edit_form();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::edit_form *m_ui;
};

#endif // EDIT_FORM_H
