#include "cbuildindig.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CBuildinDig w;
    w.show();

    return QApplication::exec();
}
