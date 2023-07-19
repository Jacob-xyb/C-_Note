#include <iostream>
using namespace std;

/// @brief & �����㣬ͬ1��Ϊ1
void Func_BitwiseAND()
{
    int x1 = 0b111;
    int x2 = 0b010;
    cout << (x1 & x2) << endl;  // 2; 010
}

/// @brief | �����㣬ͬ0��Ϊ0
void Func_BitwiseOR()
{
    int x1 = 0b111;
    int x2 = 0b010;
    cout << (x1 | x2) << endl;  // 7; 0b111
}

/// @brief ^ �������, ��ͬΪ0����ͬΪ1
void Func_BitwiseXOR()
{
	int x = 1;	// ����������ʵ�� 0 �� 1 �Ľ���
	cout << (x ^ 1) << " " << (x ^ 0) << endl;  // 0 1
	x ^= 1;
	cout << x << endl;  // 0
}

int main()
{
    Func_BitwiseXOR();
    return 0;
}