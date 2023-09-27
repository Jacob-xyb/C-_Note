#include "TestQVector.h"
#include <qobject.h>
#include <qDebug>

class People
{
public:
	int age;
	int id;
};


void TestQVector::QVector_copy()
{
	std::vector<int> arr = { 1, 2, 3 };
	QVector<int> qvi({ 1, 2, 3 });
	qDebug() << qvi;

	QVector<int> qvi2 = qvi;	// ��� qvi2 ���� qvi ����
	qvi2[0] = 99;
	qDebug() << qvi2 << qvi;
}

void TestQVector::QVector_copy2()
{
	QList<People> qv;
	QList<People> qv2 = qv;
	qv2[0].age = 18;
	qDebug() << qv[0].age;
}

void TestQVector::QVector_initByStdVector()
{
	std::vector<int> arr = { 1, 2, 3 };
	QVector<int> qvi(arr.begin(), arr.end());

	qDebug() << qvi;

	QVector<int> qvi2 = qvi;	// ǳ����
	qvi2[0] = 99;
	qDebug() << qvi2 << qvi;
}
