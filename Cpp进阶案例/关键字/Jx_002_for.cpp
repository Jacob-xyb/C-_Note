#include "../Jx_���װ���.h"

//�о�һ��forѭ���еı���
void variable_in_for001()
{
	//��python��ͬ��C++ for �еı�������ѭ������ʱ�ᱻ�ͷŵ�
	for (int i = 0; i < 3; i++)
	{
		cout << i << " ";
	}
	cout << endl;
	//cout << i << endl;	//error:δ�����ʶ��"i"

	//��������������һ��ʵ���أ�
	int idx = 0;
	for (idx; idx < 3; idx++)	//����ʵ��ʱ����д�ȽϹ淶
	//for (idx = -1; idx < 3; idx++)	//Ҳ�������¸�ֵ
	//for (; idx < 3; idx++)	//��Ȼ��дҲ���ᱨ��
	//for (idx; idx < 3; idx += 2)	// Ҳ���Ըı䲽��
	{
		cout << idx << " ";
	}
	cout << endl;
	cout << idx << endl;	//3
	//	���Դ���һ��ʵ��idxʱ��idxʱ��ʵʱ�ı䣬���Ҳ��ᱻ�ͷ�
}

//forѭ����������������������
//	��һ�����������ѭ����(�����ض���)
void variable_in_for002()
{
	int a;
	a = 3;
	cout << a << endl;
	//int a;	//���¶���ͻ����	//error C2086: ��int a��: �ض���
	a = 4;
	cout << a << endl;
}
//	�ڶ����������ѭ������(�����ض���)
void variable_in_for003()
{
	int a;
	a = 10;
	cout << a << endl;
	for (int i = 0; i < 5; i++)
	{
		int a;
		a = i + 1;
		cout << a << " ";
	}
	cout << endl << a << endl;	//��ᷢ�� a �ֱ����10

	//�²�forѭ��ÿ��ѭ�������ͷŵ�ѭ���ڴ����ı���
	cout << "���Ա����ı仯" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "��Χ�ռ��е�a��" << a << " ";
		int a;
		a = i + 1;
		cout << "forѭ���ռ��е�a��" << a << endl;
	}
	//	�����棬�ͺ���forѭ���ռ���û��a�����ͻ�ȥ��һ��Ѱ�ң�����оͻ����ȵ��ñ���ı���
}
//	������������϶������ض���
//		���ǣ�����һ�±����Ƿ�ᱻ�ͷŵ�(���Ǳ��ͷŵ���)
void variable_in_for004()
{
	for (int i = 0; i < 5; i++)
	{
		int a;
		a = i + 1;
		cout << "forѭ���ռ��е�a��" << a << endl;
	}
	//cout << "��Χ�ռ��е�a��" << a << " ";	//error C2065: ��a��: δ�����ı�ʶ��
}

//�о� for + while ѭ��ʱ�����ı仯
void variable_in_for005()
{
	for (int i = 0; i < 10; i++)
	{
		cout << "whileѭ��ǰ��i��" << i << endl;
		while (i<5)
		{
			i++;
		}
		cout << "whileѭ�����i��" << i << endl;
	}
	//���ۣ�whileѭ���ǿ���ֱ�Ӹı�forѭ���ı�����
}
