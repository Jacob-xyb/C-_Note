#include "../Jx_���װ���.h"

//&&
//condition1 && condition2ʱ���������ж�condition1
//condition1������ʱ��ֱ�ӷ���false����������ִ��conditon2
void test_andand001()
{
	vector<int> digits{ 9,9,9 };
	int bit = digits.size() - 1;
	while (bit >= 0 && digits[bit] == 9)
	//while (digits[bit] == 9 && bit >= 0)	//Expression: vector subscript out of range 
	{
		digits[bit] = 0;
		bit--;
	}
	for (int i = 0; i < digits.size(); i++)
	{
		cout << digits[i] << " ";
	}
	cout << endl;
}