#include "QSplitterTest.h"

QSplitterTest::QSplitterTest(QWidget *parent)
	: QDialog(parent), ui(new Ui::QSplitterTest)
{
	ui->setupUi(this);
	initUI();
}

QSplitterTest::~QSplitterTest()
{
}

void QSplitterTest::initUI()
{
	//splitterMain = new QSplitter(Qt::Horizontal, this); //�½����ָ�ڣ�ˮƽ�ָ�
}
