#include "Qt_Basic.h"
#include <QtWidgets/QApplication>  // qt��������ͷ�ļ���һ��������û��.h
#include "Qt_MetaObject.h"

int main(int argc, char* argv[])
{
	bool isUI = 1;

	QApplication a(argc, argv);

	if (isUI)
	{
		Qt_Basic w;
		w.show();
		return a.exec();
	}
	else
	{
		Qt_MetaObject obj;
		obj.Qt_MetaObject_className();

		return 0;
	}

}
