#ifndef DialogAbout_H
#define DialogAbout_H

#include <QtGui/QDialog>

namespace Ui {
    class DialogAbout;
}

class DialogAbout : public QDialog {
    Q_OBJECT
public:
    DialogAbout(QWidget *parent = 0);
    ~DialogAbout();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogAbout *m_ui;

private slots:
    void on_pushButton_released();
};

#endif // DialogAbout_H
