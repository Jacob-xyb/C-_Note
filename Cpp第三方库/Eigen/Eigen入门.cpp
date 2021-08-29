#include "../�����������.h"
using namespace Eigen;

//MatrixXd
//	��ʶEigen����
void Eigen_introduction_started_001()
{
	MatrixXd m(2, 2);	// MatrixXd ��ʾ���Ƕ�̬���飬��ʼ����ʱ��ָ�����������������
	cout << m << endl;	// eigen������<<�����������ֱ�����eigen�����ֵ
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);
	std::cout << m << std::endl;
}
// Matrices and vectors:Eg001
void Eigen_introduction_started_002()
{
	//��ʼ����̬����m,ʹ��Random����,��ʼ����ֵ��[-1,1]������,�����С3X3
	MatrixXd m = MatrixXd::Random(3, 3);
	cout << m << endl;
	//MatrixXd::Constant(3, 3, 1.2)��ʼ��3X3����,�����������ֵΪ����,ȫ��Ϊ1.2
	//	Eigen������ + �������������������ͬ�������������������,��Ӧλ���ϵ�ֵ���
	m = (m + MatrixXd::Constant(3, 3, 1.2));  
	//���� �� ����
	m *= 100;
	cout << "m =" << endl << m << endl;

	//����һ������ v len = 3��
	VectorXd v(3);	//ֻ�Ƕ����˳ߴ�
	//	�� STL ��ͬ��û�г�ʼ��������δ��ʼ���ڴ�ռ䣬���Է���
	cout << v[0] << endl;
	//���ų�ʼ����Ӣ�ģ�comma-initializer,Eigenδ�ṩc++11 ��{}��ʼ����ʽ
	v << 1, 2, 3;
	//	eigen������<<�����������ֱ�����Eigen������ֵ
	//		����Eigen��һά����Ĭ��Ϊ������
	cout << "v = " << endl << v << endl;
	//�����������ĳ˷�
	cout << "m * v =" << endl << m * v << endl;
}
// Matrices and vectors:Eg002
void Eigen_introduction_started_003()
{
	//MatrixXd m = MatrixXd::Random(3, 3);
	//m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
	//cout << "m =" << endl << m << endl;
	//VectorXd v(3);
	//v << 1, 2, 3;
	//cout << "m * v =" << endl << m * v << endl;

	//һ�´���ʵ�ֵĹ�����������ȫһ��
	//����ʵ�ַ�ʽ���в�ͬ�������һ�����ӣ����´������Ĳ����˷���ʵ��
	Matrix3d m = Matrix3d::Random();
	m = (m + Matrix3d::Constant(1.2)) * 50;
	cout << "m =" << endl << m << endl;
	Vector3d v(1, 2, 3);
	cout << "m * v =" << endl << m * v << endl;
}

//comma-initializer
//	�߶�һ��Ҫһ��
void Eigen_introduction_Jx003()
{
	RowVectorXd vec1(3);
	vec1 << 1, 2, 3;
	std::cout << "vec1 = " << vec1 << std::endl;

	RowVectorXd vec2(4);
	vec2 << 1, 4, 9, 16;
	std::cout << "vec2 = " << vec2 << std::endl;

	RowVectorXd joined(7);
	joined << vec1, vec2;	//ͬ�����������������ϲ�
	std::cout << "joined = " << joined << std::endl;
}
//	���õĳ�ʼ������
void Eigen_introduction_Jx004()
{
	//�����ʼ����ʼ����ֵ��[-1,1]������,�����С3X3
	MatrixXd m0 = MatrixXd::Random(3, 3);    
	//����ֵ��ʼ��,���������ֵȫ��Ϊ2.4 ,���������ֱ��������������������ֵ
	MatrixXd m1 = MatrixXd::Constant(3, 3, 2.4);
	Matrix2d m2 = Matrix2d::Zero(); 				//���ʼ��.���������ֵȫ��Ϊ0
	Matrix3d m3 = Matrix3d::Ones();                 //���������ֵȫ����ʼ��Ϊ1
	Matrix4d m4 = Matrix4d::Identity();             //��ʼ��Ϊ��λ����
	Matrix3d m5;                                    //���ų�ʼ��
	m5 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
	cout << "m0 =" << endl << m0 << endl;
	cout << "m1 =" << endl << m1 << endl;
	cout << "m2 =" << endl << m2 << endl;
	cout << "m3 =" << endl << m3 << endl;
	cout << "m4 =" << endl << m4 << endl;
	cout << "m5 =" << endl << m5 << endl;

	MatrixXf mat = MatrixXf::Ones(2, 3);
	std::cout << "before: " << endl << mat << std::endl << std::endl;
	//�˴�ʹ������ʱ������Ȼ��ʹ�ö��ų�ʼ�����ڴ˱���ʹ��finish������������ȡʵ�ʵľ������
	mat = (MatrixXf(2, 2) << 0, 1, 2, 0).finished() * mat;    
	std::cout << "after: " << endl << mat << std::endl;
}
//	MatrixXd�е�X
void Eigen_introduction_MatrixXd_001()
{
	//Xd���Ա�Xd����
	MatrixXd m0 = MatrixXd::Random(3, 3);
	//Xd���Ա�������
	MatrixXd m1 = Matrix2d::Zero();
	cout << "m1 = " << endl << m1 << endl;
	//��˼����Xd���Ժ�����ı�����

	//������Ա�ͬ�ߴ��Xd����
	Matrix2d m2 = MatrixXd::Ones(2, 2);
	cout << "m2 = " << endl << m2 << endl;
}
//	��ȡ���гߴ�
void Eigen_introduction_MatrixXd_002()
{ 
	MatrixXd m = Matrix2d::Ones();
	cout << m << endl;
	m.resize(4, 3);
	std::cout << "The matrix m is of size "
		<< m.rows() << "x" << m.cols() << std::endl;
	std::cout << "It has " << m.size() << " coefficients" << std::endl;
	VectorXd v(2);
	v.resize(5);
	std::cout << "The vector v is of size " << v.size() << std::endl;
	std::cout << "As a matrix, v is of size "
		<< v.rows() << "x" << v.cols() << std::endl;
}

//The Matrix class
//	Storage orders
void Eigen_introduction_Storage_orders_001()
{
	Matrix<int, 3, 4, ColMajor> Acolmajor;
	Acolmajor << 8, 2, 2, 9,
				 9, 1, 4, 4,
				 3, 5, 4, 5;
	cout << "The matrix A:" << endl;
	cout << Acolmajor << endl << endl;

	cout << "In memory (column-major):" << endl;
	for (int i = 0; i < Acolmajor.size(); i++)
	  cout << *(Acolmajor.data() + i) << "  ";
	cout << endl << endl;

	Matrix<int, 3, 4, RowMajor> Arowmajor = Acolmajor;
	cout << "In memory (row-major):" << endl;
	for (int i = 0; i < Arowmajor.size(); i++)
	  cout << *(Arowmajor.data() + i) << "  ";
	cout << endl << endl;
}
//	�򵥲���
void Eigen_introduction_MatrixClass_001()
{
	//Matrix����������ģ�����
	//	Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
	Matrix <double, 3, 2> m1;	//Ĭ���������ȴ洢
	cout << m1 << endl;
	Array33f arr(2);	//ֻ�ṩ��Array33f ��>10�Ĳ�û���ṩ�����Բ����������
	cout << arr << endl;
	//why arr(2)���Խ��и�ֵ��
	//	���� ArrayXf ()����ֻ������һ������ȷ��X��ֵ
	//ArrayXf arr1(4)(2);	//error
	//ArrayXf arr1(4,2);	//error
	ArrayXf arr1(4);
	cout << arr1 << endl;
	//����˼·���Գ�ʼ��	//����Constant����
	ArrayXf arr2 = ArrayXXf::Constant(4,1,2);
	cout << arr2 << endl;
}
//	Constructors
void Eigen_MatrixClass_Constructors_001()
{
	//If C++11 is enabled, fixed-size column or row vectors of arbitrary size can be initialized by passing an arbitrary number of coefficients:
	Matrix<int, 5, 1> v1{ 1, 2, 3, 4, 5 };	//double '{}' is also ok.
	cout << v1 << endl;

	//In the general case of matrices and vectors with either fixed or runtime sizes, coefficients have to be grouped by rows and passed as an initializer list of initializer list
	//Matrix<int, 2, 3> m1{ 1, 2, 3, 4, 5, 6 };	//error!
	Matrix<int, 2, 3> m1{ {1, 2, 3}, {4, 5, 6} };	//yes!
	cout << m1 << endl;

	//For column or row vectors, implicit transposition is allowed. This means that a column vector can be initialized from a single row:
	//	Because of implicit transposition, so must be initialized by double '{}'
	VectorXd v2{ {1.5, 2.5, 3.5} };             // A column-vector with 3 coefficients
	cout << "implicit transposition:" << endl <<  v2 << endl;	//unbelievable
	RowVectorXd v2t{ {1.5, 2.5, 3.5} };
	cout << "implicit transposition:" << endl << v2t << endl;
	//	�ؿ�ģ��ԭ�ͣ�Ҳ����ʽת�ã��������ݵ�˫���ţ�����
	Matrix<int, 1, 5> v3t { 1, 2, 3, 4, 5 } ;
	cout << "Constructors" << endl << v3t << endl;
}


//The Array class
//	Array���弰��������
void Eigen_introduction_ArrayClass_001()
{
	ArrayXXf a(3, 3);
	ArrayXXf b(3, 3);
	a << 1, 2, 3,
		4, 5, 6,
		7, 8, 9;
	b << 1, 2, 3,
		1, 2, 3,
		1, 2, 3;
	cout << "a + b = " << endl << a + b << endl;
	cout << "a - 2 = " << endl << a - 2 << endl;
	cout << "a * b = " << endl << a * b << endl;
	cout << "a / b = " << endl << a / b << endl;
}
//	Array������������
void Eigen_introduction_ArrayClass_002()
{
	ArrayXXf a = ArrayXXf::Random(2, 2);     // ��ʼ��2X2  Array
	a *= 2;
	cout << "a = " << endl
		<< a << endl;
	a = a.abs();
	cout << "a.abs() = " << endl
		<< a << endl;
	cout << "a.sqrt() =" << endl
		<< a.sqrt() << endl;
	cout << "a.minCoeff() = " << endl
		<< a.minCoeff() << endl;
	cout << "a.maxCoeff() = " << endl
		<< a.maxCoeff() << endl;
}

//Matrix��Array֮����໥ת��
void Eigen_introduction_MatrixToArray_001()
{
	Array44f a1, a2;
	Matrix4f m1, m2;
	m1 = a1 * a2;                     //coeffwise�˻��������鵽�������ʽת����
	std::cout << "m1: " << std::endl << m1 << std::endl;
	a1 = m1 * m2;                     //����˻����Ӿ����������ʽת����
	std::cout << "a1: " << std::endl << a1 << std::endl;

	a2 = a1 + m1.array();             //��ֹ�������;��󣬱�����ʽת���Ժ�ſ������
	m2 = a1.matrix() + m1;    
	std::cout << "a2: " << std::endl << a2 << std::endl;
	std::cout << "m2: " << std::endl << m2 << std::endl;

	ArrayWrapper<Matrix4f> m1a(m1);   // m1a��m1.array�����ı��������ǹ�����ͬ��ϵ��
	MatrixWrapper<Array44f> a1m(a1);
}
