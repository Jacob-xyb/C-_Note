#include "../Jx_���װ���.h"

/*�����е�ֵ����*/
//�������βθı䲢����Ӱ��ʵ��
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

/*��������*/
//Ĭ�ϲ���
int func_DefaultParam_001(int a = 10, int b = 20)
{
	return a + b;
}
void func_DefaultParam_001t()
{
	//����������ݾ��ô�������ݣ��������Ĭ��ֵ
	cout << func_DefaultParam_001()			<< endl;	//30
	cout << func_DefaultParam_001(30, 40)	<< endl;	//70
	cout << func_DefaultParam_001(80)		<< endl;	//100
}
//Ĭ�ϲ�����������ʵ��
int func_DefaultParam_002(int a = 10, int b = 20);
int func_DefaultParam_002(int a, int b)
{
	return a + b;
}
void func_DefaultParam_002t()
{	
	//������������Ĭ�ϲ���������Ͳ����У���֮��Ȼ
	cout << func_DefaultParam_002() << endl;	//30
	//error C2572: ��func_DefaultParam_002��: �ض���Ĭ�ϲ��� : ���� 1s
}
//ռλ����
void PlaceholderParameters_001(int)
{
	cout << "this is a func" << endl;
}
void PlaceholderParameters_001t()
{
	//PlaceholderParameters_001();
	/*error C2660 : ��PlaceholderParameters_001��: ���������� 0 ������*/
	//ռλ����������������
	PlaceholderParameters_001(1);
	// ռλ������������Ĭ�ϲ�������ʱ���Բ��ô���
}