#include <iostream>
using namespace std;

int main()
{
	string temp;
	cout << "input:" << endl;
	cin >> temp;
	if (temp == "")
	{
		cout << "����Ϊ��" << endl;
	}
	else
	{
		cout << "�س���Ч" << endl;
	}

	system("pause");
	return 0;
}