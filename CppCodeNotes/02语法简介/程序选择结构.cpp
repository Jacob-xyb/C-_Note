#include "Transfer.h"


// ��Ŀ����� Exp1 ? Exp2 : Exp3;

void TripletOperator() {
	int a = 10; int b = 20; int c = 0;
	c = (a > b ? a : b);  // c ���� a b ������ֵ

	std::cout << "��Ŀ��������ڷ��أ�" << std::endl;
	std::cout << c << std::endl;	// 20

	std::cout << "��Ŀ��������ڸ�ֵ��" << std::endl;
	(a > b ? a : b) = 100;
	std::cout << b << std::endl;	// 100
}
