/*
��������Ѱˮ�ɻ����� by (do ... while ...)
˵����ˮ�ɻ����֣�һ��3λ����ÿ��λ�ϵ����ֵ�3����֮�͵���������
������do while �������3λ���е�ˮ�ɻ�����
*/

#include <iostream>
using namespace std;

int main(){

    int num = 100;
	int sum = 0;
	do
	{
		int a = 0; int b = 0; int c = 0;
		a = num % 10;   // ��ȡ��λ��
        b = num / 10 % 10;  // ��ȡʮλ��
        c = num / 100;  // ��ȡ��λ��
		if (num == a*a*a + b*b*b + c*c*c)
		{
			cout << num << endl;
		}
		num++;
	} while (num < 1000);

    system("pause");

    return 0;

}
