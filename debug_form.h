#ifndef DEBUG_FORM_H
#define DEBUG_FORM_H

#include <QtGui/QWidget>

namespace Ui {
    class debug_form;
}

class debug_form : public QWidget {
    Q_OBJECT
public:
    debug_form(QWidget *parent = 0);
    ~debug_form();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::debug_form *m_ui;
};

#endif // DEBUG_FORM_H
