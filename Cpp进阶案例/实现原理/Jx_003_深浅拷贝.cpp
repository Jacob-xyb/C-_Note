#include "../Jx_���װ���.h"

// = ���鸳ֵ���������ǳ����
//	�²������	// ��ʵ֤�� = �����������
void copy_Jx001()
{
	vector<int> vec_v1{ 1,2,3,4,5,6 };
	vector<int> vec_v2;
	vec_v2 = vec_v1;
	for (int i = 0; i < vec_v2.size(); i++)
	{
		vec_v2[i] ++;
		cout << vec_v1[i] << " ";
	}
	cout << endl;
}