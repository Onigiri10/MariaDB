#include "mariadbtest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MariaDBTest w;
    w.show();
    return a.exec();
}
