#include "../�����������.h"

template<typename T>
using Mat2 = Matrix<T, 2, 2>;

//template + using �Զ�����������
void Eigen_bilibili_001()
{
	Mat2<int> m1;
	m1 << 1, 1,
		1, 1;
	cout << "m1:" << endl <<m1 << endl;
	//�о��е㻨�����..
	Matrix<int, 2, 2> m2(m1);
	cout << "m2:" << endl << m2 << endl;
}
//Eigen���ú���
void Eigen_bilibili_002()
{
	//���ù���
	MatrixXd m1 = MatrixXd::Zero(2, 2);
	MatrixXd m2 = MatrixXd::Ones(2, 2);
	MatrixXd m3 = MatrixXd::Identity(2, 2);
	MatrixXd m4 = MatrixXd::Random(2, 2);
	RowVectorXd v1 = RowVectorXd::LinSpaced(4,1,4);	//��size,low,high��
	cout << "���������� " << v1 << endl;
	//���ò���
	m1.setOnes();
	cout << "������Ϊ1" << endl << m1 << endl;
	m1.setZero();
	cout << "������Ϊ0" << endl << m1 << endl;
	m1.setRandom();
	cout << "�������" << endl << m1 << endl;
	m1.setConstant(6);
	cout << "������Ϊȷ�ϳ���" << endl << m1 << endl;
	m1.setIdentity();
	cout << "������Ϊ�ԽǾ���" << endl << m1 << endl;
	//m1.setLinSpaced(4,1,4);	//ֻ����������

	/*�ټ�*/
	//setUnit(index i)	//vector(i) = 1�������Ϊ0
	v1.setUnit(1);
	cout << "��������" << endl << v1 << endl;
	//setUnit(new size num, index i)	//vector.size() = num ; vector(i) = 1�������Ϊ0
	v1.setUnit(3,1);
	cout << "������Ϊ�Խǵ�λ����" << endl << v1 << endl;


}
//Eigen�����������
void Eigen_bilibili_003()
{
	MatrixXd m1 = MatrixXd::Random(2, 2);
	cout << "ԭ����"   << endl << m1 << endl;
	cout << "ת�þ���" << endl << m1.transpose() << endl;
	cout << "�������" << endl << m1.conjugate() << endl;
	cout << "�����"   << endl << m1.inverse() << endl;
	cout << "�������" << endl << m1.adjoint() << endl;
}
//Vector�����
void Eigen_bilibili_004()
{
	VectorXd v(9);
	v << 1, 2, 3, 4, 5, 6, 7, 8, 9;
	cout << "ԭ������ " << v.transpose() << endl;
	cout << "ǰ������ " << v.head(3).transpose() << endl;
	cout << "�������� " << v.tail(3).transpose() << endl;
	cout << "�м�������" << v.segment(3, 3).transpose() << endl;
}
//Matrix�����
void Eigen_bilibili_005()
{
	MatrixXd m(4, 4);
	m << 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16;
	cout << "ԭ����" << endl << m << endl;
	cout << "��һ��" << endl << m.col(0) << endl;
	cout << "��һ��" << endl << m.row(0) << endl;
	/*block�ĸ�����*/
	//ǰ������������ʼԪ�ص����б�ǩ
	//������������ȡ�����ж�����
	cout << "�Ӿ���" << endl << m.block(0,1,3,2) << endl;
	//block<3, 2>(0, 1) �����෴��<>���Ǿ���ߴ磬()������ʼλ��
	cout << "�Ӿ���" << endl << m.block<3, 2>(0, 1) << endl;
}

