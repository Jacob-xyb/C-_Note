#include "../�����������.h"

//template + using �Զ�����������
template<typename T>
using Mat2 = Matrix<T, 2, 2>;
void Eigen_QuickCheck_001()
{
	Mat2<int> m1;
	m1 << 1, 1,
		1, 1;
	cout << "m1:" << endl <<m1 << endl;
	//�о��е㻨�����..
	Matrix<int, 2, 2> m2(m1);
	cout << "m2:" << endl << m2 << endl;
}

//Eigen������
void Eigen_QuickCheck_002()
{
	//δ��ʼ������
	Matrix<double, 3, 3> A;                 // �̶��������������ľ����Matrix3dһ��.
	Matrix<double, 3, Dynamic> B;           // �̶�����.
	Matrix<double, Dynamic, Dynamic> C;     // ��MatrixXdһ��.
	Matrix<double, 3, 3, RowMajor> E;       // ���д洢; Ĭ�ϰ��д洢.
	Matrix3f P, Q, R;                       // 3x3 float ����.
	Vector3f x, y, z;                       // 3x1 float ������.
	RowVector3f a, b, c;                    // 1x3 float ������.
	VectorXd v;                             // ��̬����double��������
	// Eigen			// Matlab             // comments
	A.size();	//9		// length(A)          // ϵ������
	A.rows();			// size(A,1)          // ��������
	A.cols();			// size(A,2)          // ��������
	//x(i);				// x(i+1)             // �±�0��ʼ
	//A(i, j);          // C(i+1,j+1)         // �±�0��ʼ
}

//Eigen���þ���
void Eigen_QuickCheck_003()
{
	//���þ��󹹽�
	MatrixXd m1 = MatrixXd::Zero(2, 2);					//�����
	MatrixXd m2 = MatrixXd::Ones(2, 2);					//ȫһ����
	MatrixXd m3 = MatrixXd::Identity(2, 2);				//��λ����
	MatrixXd m4 = MatrixXd::Random(2, 2);				//�������[-1,1]
	RowVectorXd v1 = RowVectorXd::LinSpaced(4, 1, 4);	//���Էֲ���size,low,high��
	cout << "���������� " << v1 << endl;
	//���þ������ò���
	m1.setOnes();
	cout << "������Ϊ1" << endl << m1 << endl;
	m1.setZero();
	cout << "������Ϊ0" << endl << m1 << endl;
	m1.setRandom();
	cout << "�������" << endl << m1 << endl;
	m1.setConstant(6);
	cout << "������Ϊȷ�ϳ���(setConstant)" << endl << m1 << endl;
	m1.setIdentity();
	cout << "������Ϊ�ԽǾ���" << endl << m1 << endl;
	//m1.setLinSpaced(4,1,4);	//ֻ����������
	m1.fill(6);
	cout << "������Ϊȷ�ϳ���(fill)" << endl << m1 << endl;
}


//Eigen�����������
void Eigen_QuickCheck_004()
{
	MatrixXd m1 = MatrixXd::Random(2, 2);
	cout << "ԭ����" << endl << m1 << endl;
	cout << "ת�þ���" << endl << m1.transpose() << endl;
	cout << "�������" << endl << m1.conjugate() << endl;
	cout << "�����" << endl << m1.inverse() << endl;
	cout << "�������" << endl << m1.adjoint() << endl;
}


//Eigen���ú���
void Eigen_QuickCheck_005()
{
	MatrixXd m1 = MatrixXd::Zero(2, 2);
	RowVectorXd v1 = RowVectorXd::LinSpaced(4, 1, 4);	//��size,low,high��

	/*�ټ�*/
	//setUnit(index i)	//vector(i) = 1�������Ϊ0
	v1.setUnit(1);
	cout << "��������" << endl << v1 << endl;
	//setUnit(new size num, index i)	//vector.size() = num ; vector(i) = 1�������Ϊ0
	v1.setUnit(3,1);
	cout << "������Ϊ�Խǵ�λ����" << endl << v1 << endl;
}


//Vector�����
void Eigen_QuickCheck_006()
{
	RowVectorXd v(9);
	v << 1, 2, 3, 4, 5, 6, 7, 8, 9;
	//Eigen									// Matlab
	//v.head(n) \ v.head<n>()				// v(1:n)	����������ȡǰn��[vector]
	//v.tail(n) \ v.tail<n>()				// v(end - n + 1: end)ͬ��
	//v.segment(i, n) \ v.segment<n>(i)     // v(i+1 : i+n)ͬ��

	//����
	cout << "ԭ������ "		<< v				<< endl;
	cout << "ǰ������ "		<< v.head(3)		<< endl;
	cout << "�������� "		<< v.tail(3)		<< endl;
	cout << "�м�������"	<< v.segment(3, 3)	<< endl;
}


//Matrix�����
void Eigen_QuickCheck_007()
{
	MatrixXd m(4, 4);
	m << 1, 2, 3, 4,
		 5, 6, 7, 8,
		 9, 10, 11, 12,
		 13, 14, 15, 16;
	cout << "ԭ����" << endl << m << endl;

	//Eigen												// Matlab
	//m.row(i)											// m(i+1, :) ��i������
	//m.col(j)											// m(:, j+1) ��j������
	//m.topRows(rows) \ m.topRows<rows>()				// m(1:rows, :) ǰrows�� 
	//m.middleRows(i, rows) \ m.middleRows<rows>(i)		// m(i+1:i+rows, :) ��[i:rows]�� 
	//m.bottomRows(rows) \ m.bottomRows<rows>()			// m(end-rows+1:end, :) ��rows�� 
	//m.leftCols(cols) \ m.leftCols<cols>()				// m(:, 1:cols) ǰcols��
	//m.middleCols(j, cols) \ m.middleCols<cols>(j)	    // m(:, j+1:j+cols) ��[j:cols]��
	//m.rightCols(cols) \ m.rightCols<cols>()			// m(:, end-cols+1:end) ��cols�� 
	//m.block(i, j, rows, cols) \ m.block<rows, cols>(i, j)	
														// m(i+1 : i+rows, j+1 : j+cols)i,j��ʼ��rows��cols��
	//	ȡ�� \ (rows, cols) == <rows, cols>()
	//m.topLeftCorner(rows, cols)        // m(1:rows, 1:cols)�����rows�У�cols��
	//m.topRightCorner(rows, cols)       // m(1:rows, end-cols+1:end)���ҽ�rows�У�cols��
	//m.bottomLeftCorner(rows, cols)     // m(end-rows+1:end, 1:cols)�����rows�У�cols��
	//m.bottomRightCorner(rows, cols)    // m(end-rows+1:end, end-cols+1:end)���ҽ�rows�У�cols��
									
	//����
	cout << "��һ��"	<< endl << m.row(0)				<< endl;
	cout << "��һ��"	<< endl << m.col(0).transpose()	<< endl;
	cout << "ǰ����"	<< endl << m.topRows(2)			<< endl;
	cout << "�м�����"	<< endl << m.middleRows(1,2)	<< endl;
	cout << "������"	<< endl << m.bottomRows(2)		<< endl;
	cout << "ǰ����"	<< endl << m.leftCols(2)		<< endl;
	cout << "�м�����"	<< endl << m.middleCols(1, 2)	<< endl;
	cout << "������"	<< endl << m.rightCols(2)		<< endl;
	cout << "�Ӿ���"	<< endl << m.block(0,0,2,2)		<< endl;

	cout << "���϶����Ӿ���" << endl << m.topLeftCorner(2, 2)		<< endl;
	cout << "���϶����Ӿ���" << endl << m.topRightCorner(2, 2)		<< endl;
	cout << "���¶����Ӿ���" << endl << m.bottomLeftCorner(2, 2)	<< endl;
	cout << "���¶����Ӿ���" << endl << m.bottomRightCorner(2,2)	<< endl;

}

