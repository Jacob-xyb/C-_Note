#include "../Jx_���װ���.h"

//float��double
void dataType001()
{
	//float��doubleĬ��ֻ��ʾ6λ��Ч����
	//	float�����7λ��Ч����
	//	double�����15λ��Ч����
	float a = 3.1415926124;
	cout << a << endl;
	double b = 3.1415926124;
	cout << b << endl;
	cout << "��ֻ��ʾ6λ��Ч����" << endl;
}

void scientific_notation001()
{
	float a = 3e3;
	cout << a << endl;
	float b = 3.1e10;	//��������������Ч����֮����Կ�ѧ��������ʽ��ʾ
	cout << b << endl;
	float c = 3.2e-5;
	cout << c << endl;
	float d = 3.2e-3;
	cout << d << endl;

	//������Чλ�����������Ƿ��ܽ�������
	cout << endl;
	b += b;
	cout << b << endl;	//���Խ�������
}

//char
void dataType002()
{
	char ch1 = 'a';	//ע�⣺�ַ�һ��Ҫ�õ�����
	cout << sizeof(ch1) << endl;
	char ch2 = '��';
	cout << sizeof(ch2) << endl;	//��Ӣ�Ķ�ֻռһ���ַ�
	ch2 = ' ';
	cout << sizeof(ch2) << endl;	//spaceҲ����һ���ַ�
	//����ֵ��ǣ�1~4��space��ֻռһ���ַ�������5��spaceȴ�ᱨ��
	//	�������1~4��space�Ƿ�һ�����ֱ������ʲô
	cout << "1��space��" << ch1 << ch2 << ch1 << endl;
	ch2 = '  ';
	cout << "2��space��" << ch1 << ch2 << ch1 << endl;
	ch2 = '   ';
	cout << "3��space��" << ch1 << ch2 << ch1 << endl;
	ch2 = '    ';
	cout << "4��space��" << ch1 << ch2 << ch1 << endl;
	//	���֤����1~4��space��ֻ���һ��space
	//		�����εķ��֣���������space
	ch1 = 'aaaa';
	cout << "aaaa�����ʲô��" << ch1 << endl;
	ch1 = 'abcd';
	cout << "abcd�����ʲô��" << ch1 << endl;
	ch1 = 'abc1';
	cout << "abc1�����ʲô��" << ch1 << endl;
	//		����һ���ַ��������ڿ����ϸ��������ǿ��Գ���0<x<=4���ַ���
	//		����Щ�ַ������һ���ַ�������ֵ
	//		���һ�β���
	ch1 = 'abc ';
	cout << "abcspace�����ʲô��" << ch1 << endl;
	//�鿴ASCII��
	cout << "�鿴ASCII�룺" << (int)ch1 << endl;
}

//bool
void dataType003()
{
	bool flag = true;
	cout << flag << endl;	//true��1��bool��0

	if (flag == 1)	//������ֻ����1��true
	{
		cout << "�ж�ʱ��flag����Ϊ1" << endl;
		if (flag == true)
		{
			cout << "�ж�ʱ,flagҲ����Ϊtrue" << endl;
		}
		if (flag == 100)
		{
			cout << "�Ƿ���Գ�Ϊ���з�0" << endl;
		}
	}

	cout << "������flag��ֵ��" << endl;
	cin >> flag;	//���ֳ���0�ⶼ���棬���������ⶼ�Ǽ�
	cout << "�����flag��ֵ��" << flag << endl;
}

//array
//	һά����
void dataType004()
{
	//һά����������������ʽ

	//	1.type arrayName [ arraySize ];
	//		ʹ��δ��ʼ�����ڴ棬���Ჹ0�����ǿ��Ե���
	int arr1[5];
	cout << arr1[0] << endl;	//-858993460
	arr1[0] = 66;
	cout << arr1[0] << endl;	//66

	//	2.type arrayName [ arraySize ] = {};	// ���� arraySize �� 0
	//		type arrayName[arraySize] = { val1, val2 ... };	// û�ж���Ļ����Զ��� 0
	//		���Ϸ������Ჹ0
	int arr2[5] = {};
	cout << arr2[0] << endl;

	// 3.type arrayName[] = { val1, val2 ...};
	//		���Ȼ�������������ݸ�������
	int arr3[] = { 5,4,3,2,1 };
	cout << arr3[0] << endl;
}
//	��ά����
void dataType005()
{
	//��ά�����ж���������ʽ

	//	1.type arrayName [row][col];
	//		ʹ��δ��ʼ�����ڴ棬���Ჹ0

	//	2.type arrayName [row][col] = {};
	//		ʹ�ó�ʼ�����ڴ棬�Ჹ0
	int v2[3][3] = {};
	cout << v2[0][0] << endl;

	//	3.type arrayName [row][col] = {{ val11, val12 ...},{ val21, val22 ...}};
	//		û�ж���Ļ����Զ��� 0		// ����ֱ�ۣ���߿ɶ���

	//	4.type arrayName [row][col] = {val11, val12 ...};
	//		���ַ�ʽ���ݸ������ܳ��� row*col,����ĻᲹ0		
	//		index������Ҳ���ᱨ�����ȡ0
	int v4[2][2] = { 1,2,3 };
	cout << "v4���һ����" << v4[1][1] << endl;	//0
	//int v4_1[2][2] = { 1,2,3,4,5 };	//error:��ʼֵ�趨��̫��

	//	5.type arrayName [][col] = {val11, val12 ...};
	//		���� n*col �Ķ�ά���飨���󣩣�����ĻᲹ0
	int v5[][5] = { 1,2,3 };
	cout << "v5.size(): " << sizeof(v5) / sizeof(int) << endl;	//5
	int v5_1[][5] = { 1,2,3,4,5,6 };	//�²���10����λ
	cout << "v5_1.size(): " << sizeof(v5_1) / sizeof(int) << endl;	//10
}