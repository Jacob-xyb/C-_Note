#include "Qt_Basic.h"
#include <QtWidgets/QApplication>  // qt��������ͷ�ļ���һ��������û��.h

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt_Basic w;
    w.show();
    return a.exec();
}
