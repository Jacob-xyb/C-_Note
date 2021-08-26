#include "../�����������.h"
using namespace Eigen;

//MatrixXd
//	��ʶһ��Eigen����
void Eigen_introduction_Jx001()
{
	MatrixXd m(2, 2);	// MatrixXd ��ʾ���Ƕ�̬���飬��ʼ����ʱ��ָ�����������������
	cout << m << endl;	// eigen������<<�����������ֱ�����eigen�����ֵ
	m(0, 0) = 1;
	m(0, 1) = 2;
	m(1, 0) = 3;
	m(1, 1) = m(0, 0) + m(1, 0);
	cout << m << endl;
}
void Eigen_introduction_Jx002()
{
	//��ʼ����̬����m,ʹ��Random����,��ʼ����ֵ��[-1,1]������,�����С3X3
	MatrixXd m = MatrixXd::Random(3, 3);
	cout << m << endl;
	m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;   // MatrixXd::Constant(3, 3, 1.2)��ʼ��3X3����,�����������ֵΪ����,ȫ��Ϊ1.2
	// Eigen������+ �������������������ͬ�������������������,��Ӧλ���ϵ�ֵ���
	cout << "m =" << endl << m << endl;
	VectorXd v(3);
	v << 1, 2, 3;                                   //���ų�ʼ����Ӣ�ģ�comma-initializer,Eigenδ�ṩc++11 ��{}��ʼ����ʽ
	cout << "m * v =" << endl << m * v << endl;
}