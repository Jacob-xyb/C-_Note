#include "PointNotes.h"
#include <iostream>

using namespace std;

void PointNotes::Func_PointDefine()
{
	int a = 10;
	int* p;

	// ��ָ���¼���� a �ĵ�ַ
	p = &a;
	cout << p << endl;

	// ++ָ���ʹ��
	// ����ͨ�������õķ�ʽ���ҵ�ָ��ָ����ڴ�	// *p
	cout << "pָ����ڴ�����Ϊ�� " << *p << endl;
	// ͨ�� *p ���Է��ʺͶ�д �ڴ�����
	*p = 1000;
	cout << "��д��a��ֵ��Ϊ�ˣ�" << a << endl;
	cout << "��ʱ��*p��ֵ��Ϊ�ˣ� " << *p << endl;
	cout << "����p��ֵ��û�б��Ϊ�� " << p << endl;
}
