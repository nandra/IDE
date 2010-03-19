#ifndef PROJECT_FORM_H
#define PROJECT_FORM_H

#include <QtGui/QWidget>

namespace Ui {
    class project_form;
}

class project_form : public QWidget {
    Q_OBJECT
public:
    project_form(QWidget *parent = 0);
    ~project_form();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::project_form *m_ui;
};

#endif // PROJECT_FORM_H
