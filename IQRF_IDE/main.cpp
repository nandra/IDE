#include <QtGui/QApplication>
#include "main_form.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    main_form w;
    w.show();
    return a.exec();
}
