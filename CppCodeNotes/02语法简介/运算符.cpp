#include "Transfer.h"


// ���ȼ����� > ��������� > ��ϵ����� > && > || > ��ֵ�����

void ArithmeticOperator() {
	// ����������� +  -  *  /  %  ^  !
	float fA = 10.18;
	float fB = 08.28;
	int iA = 777;
	int iB = 2;
	
	// 1.�Ӽ��˳�
	std::cout << "1.�Ӽ��˳���" << std::endl;
	std::cout << "10.10 + 08.28 = " << fA + fB << std::endl;
	std::cout << "10.10 - 08.28 = " << fA - fB << std::endl;
	std::cout << "10.10 * 08.28 = " << fA * fB << std::endl;
	std::cout << "10.10 / 08.28 = " << fA / fB << std::endl;
	//   �Ƚ�����ģ�int / int ֱ�ӻ�ʡȥС��������
	std::cout << "������Щ���⣺" << std::endl;
	std::cout << "float / int = float: " << fA / iB << std::endl;
	std::cout << "int / float = float: " << iA / fB << std::endl;
	std::cout << "int / int = int: " << iA / iB << std::endl;	

	// 2. int ȡ��; % ȡ��
	std::cout << "ȡ��ȡ����" << std::endl;
	std::cout << "777 / 2 = " << iA / iB << std::endl;		// ������������ȡ��
	std::cout << "777 % 2 = " << iA % iB << std::endl;

}

void BinaryRecursion(int n)
{
	int a = n % 2;
	n >>= 1;
	if (n != 0)
	{
		BinaryRecursion(n);
	}
	std::cout << a;
}

void AssignmentOperator() {
	// �������������صĸ�ֵ������Ͳ�������

	// λ�����
	std::cout << "λ���㣺" << std::endl;
	std::cout << "1 << 2 = " << (1 << 2) << std::endl;		// 4
	std::cout << "1 << 4 = " << (1 << 4) << std::endl;		// 16
	std::cout << "8 >> 1 = " << (8 >> 1) << std::endl;		// 4
	std::cout << std::endl;

	// �������
	std::cout << "������㣺" << std::endl;
	std::cout << "1100 & 100 = ";	// 1100 & 100 = 100
	BinaryRecursion(0xc & 0x4);
	std::cout << std::endl;		
	std::cout << "1010 | 110 = ";	// 1010 & 110 = 1110
	BinaryRecursion(10 | 6);
	std::cout << std::endl;		
	std::cout << "1010 ^ 110 = ";	// 1010 & 110 = 1100
	BinaryRecursion(10 ^ 6);
	std::cout << std::endl;
}

void CommaOperator() {
	int a = 1;
	int b = 2;
	int c = (a, b++, a+=b);
	std::cout << c << std::endl;		// 4
	// ����˳��Ϊ��a=1, b=2+1=3, a=a+b=1+3=4, c=a=4
}

