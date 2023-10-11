#include "QCustomPlotTest.h"

QCustomPlotTest::QCustomPlotTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QCustomPlotTestClass())
{
    ui->setupUi(this);
    draw_parabola();
}

QCustomPlotTest::~QCustomPlotTest()
{
    delete ui;
}

void QCustomPlotTest::draw_parabola()
{
    // �������ݣ���������������
    QVector<double> x(101), y(101); //��ʼ������x��y
    for (int i = 0; i < 101; ++i)
    {
        x[i] = i / 50.0 - 1; // x��Χ[-1,1]
        y[i] = x[i] * x[i]; // y=x*x
    }
    ui->customPlot->addGraph();//����������ߣ�һ��ͼ������ж���������ߣ�

    // graph(0);���Ի�ȡĳ���������ߣ�������Ⱥ�����
    // setData();Ϊ�������߹�������
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->graph(0)->setName("��һ��ʾ��");// ����ͼ������
    // Ϊ��������ӱ�ǩ
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // ����������ķ�Χ���Կ�����������
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->legend->setVisible(true); // ��ʾͼ��
    // �ػ�ͼ��
    ui->customPlot->replot();
}
