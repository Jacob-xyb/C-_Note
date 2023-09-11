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
	qDebug() << s1.split(QRegExp("[\\s\,]"), Qt::SplitBehaviorFlags::SkipEmptyParts);	// \\s �������пո񣬻س������е�
}
