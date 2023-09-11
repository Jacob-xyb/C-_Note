#include "TestQByteArray.h"
#include <QDebug>

void TestQByteArray::QByteArray_Init()
{
	// ��ʼ������1�� const char* ���캯��
	QByteArray ba("hello");
	qDebug() << ba << ba.size();

	// ��ʼ������2: resize()
	QByteArray ba1;
	ba1.resize(6);	// ������ resize() �����룬��� fill(0) ��ʼ��
	qDebug() << ba1;
	ba1.fill(0);
	qDebug() << ba1;
}

void TestQByteArray::QByteArray_InitDiff()
{
	QByteArray ba1("hel\0lo");
	qDebug() << ba1 << ba1.size();	// "hel" 3 ;���ض�

	QByteArray ba2;
	ba2.resize(6);
	ba2[0] = 'h';
	ba2[1] = 'e';
	ba2[2] = 'l';
	ba2[3] = '\0';
	ba2[4] = 'l';
	ba2[5] = 'o';
	qDebug() << ba2 << ba2.size(); // "hel\x00lo" 6
}

