/*
��������������Ϸ by whileѭ��
��Ϸ�����������һ�� 1~100 ���������¶Լ��ɡ�

����Ҫ��
1.��������Ҳ²�Ĵ�����ʾ��
*/

#include <iostream>
using namespace std;
#include <ctime>  // ����ʱ��ģ��



int main() {

	srand((unsigned int)time(NULL));  // ����ʱ������һ�����������һ�� �����������Ȼ rand()ֻ����һ�� α�������
	int num = rand() % 100 + 1;
	int times = 1;
	int ans = 0;
	while (true)
	{
		cout << "��" << times++ << "�γ���" << endl;	// ��¼�²����
		cout << "����²������(1~100)�� " << endl;
		cin >> ans;

		if (ans == num)
		{
			cout << "��ϲ��¶��ˣ�" << endl;
			break;
		}
		else if (ans > num)
		{
			cout << "��´���..." << endl;
		}
		else
		{
			cout << "���С��..." << endl;
		}

		cout << endl;
	}

	system("pause");

	return 0;
}
