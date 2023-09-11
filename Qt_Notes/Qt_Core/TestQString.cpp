#include "TestQString.h"
#include <QString>
#include <qDebug>
#include <QRegExp>

void TestQString::QString_split()
{
	//�����÷�
	QString s1 = "hello sworld";
	qDebug() << s1.split(" ");


}

void TestQString::QString_split_QRegExp()
{
	//������ʽ
	QString s1 = "12.1, 2141.1, 41.6, 41.9";
	qDebug() << s1.split(QRegExp("\\s"));	// \\s �������пո񣬻س������е�
	qDebug() << s1.split(QRegExp("[\\s,]"), Qt::SplitBehaviorFlags::SkipEmptyParts);	// \\s �������пո񣬻س������е�
}

void TestQString::QString_toFloat()
{
	QString s1 = "123a";
	bool flag = false;
	float f1 = s1.toFloat(&flag);
	if (flag)
	{
		qDebug() << "successfully" << f1;
	}
	else
	{
		qDebug() << "failed" << f1;
	}

}
