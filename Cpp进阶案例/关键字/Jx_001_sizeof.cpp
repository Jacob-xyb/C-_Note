#include "../Jx_test.h"

//������sizeofӦ��
void sizeof_type001()
{
	//sizeof()���Է���һ��������ռ�ڴ��С
	//	����������������ָ����ʵ��sizeof()����
	int a[5] = { 1,2,3,4,5 };
	cout << "sizeof()ʵ��sizeof(a)��" << sizeof(a) << endl;
	int jx;		// �⽫��������ʵ�ֵĽ��
	////	--
	////	ž��һ�´��ԭ�Σ��мǲ�Ҫ��ʮ�����ƽ��мӼ�
	//cout << "&a: " <<  & a << endl;
	//cout << "&a+1: " << & a + 1 << endl;
	//cout << "&a - (&a + 1): " << &a - (&a + 1) << endl;
	////	--
	//jx = int(&a + 1) - int(&a);
	// ��ʵ���Ƕ���ָ�룺β��ַ-�׵�ַ
	cout << "Jxʵ��sizeof(a)��" << int(&a + 1) - int(&a) << endl;

	cout << "sizeof()ʵ��sizeof(a[0])��" << sizeof(a[0]) << endl;
	cout << "Jxʵ��sizeof(a[0])��" << int(a + 1) - int(a) << endl;

	//sizeof()������ֱ�Ӵ�ӡ�����������͵��ڴ�ռλ
	//cout << sizeof(int) << endl;
	//cout << sizeof(float) << endl;
}

