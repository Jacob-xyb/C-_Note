#include <iostream>
#include <bitset>
using namespace std;

/// @brief & �����㣬ͬ1��Ϊ1
void Func_BitwiseAND()
{
    int x1 = 0b111;
    int x2 = 0b010;
    cout << (x1 & x2) << endl; // 2; 010
}

/// @brief | �����㣬ͬ0��Ϊ0
void Func_BitwiseOR()
{
    int x1 = 0b111;
    int x2 = 0b010;
    cout << (x1 | x2) << endl; // 7; 0b111
}

/// @brief ^ �������, ��ͬΪ0����ͬΪ1
void Func_BitwiseXOR()
{
    // ����������ʵ�� 0 �� 1 �Ľ���
    int x = 1;
    cout << (x ^ 1) << " " << (x ^ 0) << endl; // 0 1
    x ^= 1;
    cout << x << endl; // 0
}

/// @brief ~ ȡ������
void Func_BitwiseInverse()
{
    int x = 1;
    int y = ~x;
    cout << y << endl; // -2; 1 ȡ���� -2
}

/// @brief << ��������
void Func_BitwiseLeftShift()
{
    int x = 8;
    x <<= 1;
    cout << x << endl; // 16

    int x2 = -2;
    x2 <<= 1;
    cout << x2 << endl; // -4
}

/// @brief >> ��������
void Func_BitwiseRightShift()
{
    int x = 2;
    x >>= 1;
    cout << x << endl; // 1

    int x2 = -2;
    x2 >>= 1;
    cout << x2 << endl; // -1
    x2 >>= 1;
    cout << x2 << endl; // -1; �����Ҳ�1�����Ի���-1
}

int main()
{
    Func_BitwiseInverse();
    // Func_BitwiseRightShift();

    return 0;
}