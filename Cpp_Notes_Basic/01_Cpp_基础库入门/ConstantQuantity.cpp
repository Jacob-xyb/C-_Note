#include "ConstantQuantity.h"
using namespace std;

void Constant_Const::Func_ConstAndPoint()
{
	//1.const���εĳ������ܱ��ı�
	//2.const���������ʼ��
	
	//const int a;  //Error:���������ʼ��
	const int a = 0;

	//const �� ָ��Ĺ�ϵ
	int b = 0;
	const int* p1;	//p1��ָ������ָ�����; p1�Ǳ��������Կ���������ʱ����ʼ����
	p1 = &b;

	int* const p2 = &b; //p2��ָ�������ָ�볣��;p2�ǳ�������������ʱ�����ʼ����
	int* const p3 = nullptr;  //�ÿ�ָ���ʼ��������
}

void Constant_Const::Func_ConstAndQuote()
{
	double a = 3.14;

	//��ʱ int �����ǲ����е�
	//int& val1 = a;	//Error: ���ܽ� double ��ʼ��Ϊ int&

	//���� const int& �ǿ��Ե�
	const int& val2 = a;	//��Ϊ const ��������һ���Ϸ��ռ䣬ԭ���� int temp = a; const int& val2 = temp;
	cout << val2 << endl;	// 3
}
