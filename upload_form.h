#ifndef UPLOAD_FORM_H
#define UPLOAD_FORM_H

#include <QtGui/QWidget>

namespace Ui {
    class upload_form;
}

class upload_form : public QWidget {
    Q_OBJECT
public:
    upload_form(QWidget *parent = 0);
    ~upload_form();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::upload_form *m_ui;
};

#endif // UPLOAD_FORM_H
