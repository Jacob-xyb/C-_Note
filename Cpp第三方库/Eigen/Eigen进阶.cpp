#include "../�����������.h"
using namespace Eigen;

//����һ��random_shuffle	//����
void Eigen_RandomShuffle()
{
	//����һ����������
	Eigen::VectorXi v = Eigen::VectorXi::LinSpaced(10, 0, 9);
	std::cout << v.transpose()	<< endl;
	//Eigen����Ҳ����begin()��end(),������һ��ָ��
	std::cout << "*v.begin():\t"	<< * v.begin()		<< endl;
	std::cout << "*(v.end()-1):\t"	<< * (v.end()-1)	<< endl;
	//random_shuffle
	random_shuffle(v.begin(), v.end());
	std::cout << "ת�ú�"		<< endl;
	std::cout << v.transpose()	<< endl;
}