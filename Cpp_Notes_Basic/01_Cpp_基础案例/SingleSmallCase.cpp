#include "SingleSmallCase.h"
#include <iostream>

using namespace std;

void SingleSmallCase::NumberGuessingGame()
{
	srand((unsigned int)time(NULL));  // ����ʱ������һ�����������һ�� �����������Ȼ rand()ֻ����һ�� α�������
	int num = rand() % 100 + 1;
	int times = 1;
	int ans = 0;

	while (true)
	{
		printf("�� %02d �γ���", times++);
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

	char res = getchar();
}

void SingleSmallCase::DaffodilNumber()
{
	int num = 100;
	int sum = 0;
	do
	{
		int a = 0; int b = 0; int c = 0;
		a = num % 10;   // ��ȡ��λ��
		b = num / 10 % 10;  // ��ȡʮλ��
		c = num / 100;  // ��ȡ��λ��
		if (num == a * a * a + b * b * b + c * c * c)
		{
			cout << num << endl;
		}
		num++;
	} while (num < 1000);

	char res = getchar();
}

void SingleSmallCase::BubbleSort(int* arr, int num)
{
	for (int tms = num - 1; tms > 0; tms--)       // ÿ������Ĵ����Ǵ� �ܸ���-1 ~ 1
	{
		for (int i = 0; i < tms; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				int temp = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = temp;
			}
		}
	}

	for (int i = 0; i < num; i++)
	{
		cout << arr[i] << " ";
	}
}
