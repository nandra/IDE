#ifndef TEST_FORM_H
#define TEST_FORM_H

#include <QtGui/QWidget>

namespace Ui {
    class test_form;
}

class test_form : public QWidget {
    Q_OBJECT
public:
    test_form(QWidget *parent = 0);
    ~test_form();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::test_form *m_ui;
};

#endif // TEST_FORM_H
