#include <iostream>
#include "OperatorNotes.h"
using namespace std;

#pragma region ��Ԫ�����
void TernaryOperator::Func_Basic()
{
	int a = 0;
	int b = 7;
	(a > b ? a : b) = 99;

	printf("a = %d, b = %d\n", a, b);	// a = 0, b = 99
}
#pragma endregion

#pragma region λ����
// & ������
void BitwiseOperator::Func_BitwiseAND()
{
}
// ~ �������;��ͬΪ0����ͬΪ1
void BitwiseOperator::Func_BitwiseXOR()
{
	int x = 1;	// ����������ʵ�� 0 �� 1 �Ľ���
	cout << (x ^ 1) << " " << (x ^ 0) << endl;
	x ^= 1;
	cout << x << endl;
}
// ~ ������
void BitwiseOperator::Func_BitwiseInverse()
{
	int x = 1;
	int y = ~x;	 // 1 ȡ���� -2
	cout << y << endl;
}
#pragma endregion

