#include <iostream>
using namespace std;

//��ʶ��򵥵ĵݹ�Ӧ��
//����n!
//	�ݹ�������
/*
1. �ݹ��㷨������һ������������������С��ģ�����ֱ�ӽ����
2. �ݹ��㷨�����ܸı�״̬��������������ݽ�����С�����ģ��
3. �ݹ��㷨����������������С�˹�ģ����ͬ���⣩
*/

int factorial(int n)
{
	//��С��ģ����
	if (n <= 1)	return 1;	//0!=1
	//��С��ģ����,��������
	//	n! = n*(n-1)!
	return n * factorial(n - 1);
}

int main()
{
	cout << factorial(3) << endl;
	system("pause");
	return 0;
}