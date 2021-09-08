#include "../�����������.h"
using namespace Eigen;

//����һ��random_shuffle	//����
void Eigen_RandomShuffle()
{
	//����һ����������
	Eigen::VectorXd v = Eigen::VectorXd::LinSpaced(10, 0, 9);
	std::cout << v.transpose()	<< endl;
	//Eigen����Ҳ����begin()��end(),������һ��ָ��
	std::cout << "*v.begin():\t"	<< * v.begin()		<< endl;
	std::cout << "*(v.end()-1):\t"	<< * (v.end()-1)	<< endl;
	//random_shuffle
	random_shuffle(v.begin(), v.end());
	std::cout << "ת�ú�"		<< endl;
	std::cout << v.transpose()	<< endl;
}

//Matrix��һ��
void Eigen_NormalizationMatrix()
{
	Eigen::MatrixXd m = Eigen::MatrixXd::Random(3,3);
	cout << m << endl;
	int row = m.rows();
	int col = m.cols();
	Eigen::MatrixXd normal(m);
	for (int j = 0; j < col; j++)
	{
		double xmax = m.col(j).maxCoeff();
		double xmin = m.col(j).minCoeff();
		normal.col(j) = (normal.col(j) - Eigen::VectorXd::Constant(row, xmin)) /
			(xmax - xmin);
	}
	cout << normal << endl;
}