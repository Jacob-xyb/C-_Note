#include "../Jx_test.h"

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