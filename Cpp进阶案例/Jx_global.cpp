#include "./Jx_���װ���.h"

// дһ����ӡvector<int>�ĺ����������
void printVector(vector<int>& v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}
// дһ����ӡvector<vector<int>>�ĺ����������

void printVector(vector<vector<int>>& v)
{
    for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++)
    {
        for (vector<int>::iterator jt = it->begin(); jt != it->end(); jt++)
        {
            cout << *jt << " ";
        }
        cout << endl;
    }
}
void printStart(int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << "*";
    }   
}

// int ���������ж�
void TypeInt(int* val)
{
	while (cin.fail())
	{
		cin.clear();		// ����λ���ã���仰һ��Ҫд��
		cin.ignore();		// TODO; �����������޷�����
		cout << "�������������һ��������";
		cin >> *val;
	}
}

void SleepAndClear()
{
	// clear
	// windows
	system("pause");
	system("cls");

	// mac
	// cout << "please press any key to continue...";
	// string PAUSE;
	// cin >> PAUSE;
	// system("clear");
}