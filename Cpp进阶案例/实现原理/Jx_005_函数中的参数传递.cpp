#include "../Jx_���װ���.h"

//�����е�ֵ����
//	�������βθı䲢����Ӱ���β�
void func_transmit_001(int num1, int num2)
{
	cout << "�����е�num1: " << num1 << endl;
	cout << "�����е�num2: " << num2 << endl;
	num1++; num2++;
	cout << "�����иı���num1: " << num1 << endl;
	cout << "�����иı���num2: " << num2 << endl;
}


void func_transmit_001t()
{
	int a = 10, b = 20;
	cout << "�������ʵ��a: " << a << endl;
	cout << "�������ʵ��b: " << b << endl;
	func_transmit_001(a, b);
	cout << "����ִ�к��ʵ��a: " << a << endl;
	cout << "����ִ�к��ʵ��b: " << b << endl;
}