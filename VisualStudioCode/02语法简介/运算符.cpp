#include "Transfer.h"


// ���ȼ����� > ��������� > ��ϵ����� > && > || > ��ֵ�����
void ArithmeticOperator() {
	// ����������� +  -  *  /  %  ^  !
	float fA = 10.18;
	float fB = 08.28;
	int iA = 777;
	int iB = 2;
	
	// 1.�Ӽ��˳�
	std::cout << "10.10 + 08.28 = " << fA + fB << std::endl;
	std::cout << "10.10 - 08.28 = " << fA - fB << std::endl;
	std::cout << "10.10 * 08.28 = " << fA * fB << std::endl;
	std::cout << "10.10 / 08.28 = " << fA / fB << std::endl;
	//   �Ƚ�����ģ�int / int ֱ�ӻ�ʡȥС��������
	std::cout << "������Щ����" << std::endl;
	std::cout << "float / int = float: " << fA / iB << std::endl;
	std::cout << "int / float = float: " << iA / fB << std::endl;
	std::cout << "int / int = int: " << iA / iB << std::endl;		
}
