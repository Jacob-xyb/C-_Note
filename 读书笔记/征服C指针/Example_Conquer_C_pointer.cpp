#include <stdio.h>
#include <iostream>
#include "../Proj/BookNotes_Head.h"
using namespace std;

void exp_1_1_pointer()
{
	int hoge = 5;
	int piyo = 10;
	int* hoge_p;

	/*���ÿ�������ĵ�ַ*/
	printf("&hoge..%p\n", &hoge);		//&hoge..0000003A706FF9D4
	printf("&piyo..%p\n", &piyo);		//&piyo..0000003A706FF9F4
	printf("&hoge_p..%p\n", &hoge_p);	//&hoge_p..0000003A706FFA18

	/*�� hoge �ĵ�ַ���� hoge_p */
	hoge_p = &hoge;
	printf("hoge_p..%p\n", hoge_p);		//hoge_p..0000003A706FF9D4	

	/*ͨ�� hoge_p ��� hoge ������*/
	printf("*hoge_p..%d\n", *hoge_p);	//*hoge_p..5

	/*ͨ�� hoge_p �޸� hoge ������*/
	*hoge_p = 10;
	printf("hoge..%d\n", hoge);			//hoge..10
}
void exp_1_2_pointer_calc()
{
	int hoge;
	int* hoge_p;

	/*��ָ�� hoge ��ָ�븳�� hoge_p */
	hoge_p = &hoge;
	printf("hoge_p..%p\n", hoge_p);			//hoge_p..000000A1C88FF624
	++hoge_p;
	printf("hoge_p..%p\n", hoge_p);			//hoge_p..000000A1C88FF628
	printf("hoge_p..%p\n", hoge_p + 3);		//hoge_p..000000A1C88FF634
}
void exp_1_4_array2()
{
	int array[5];
	int* p;
	int i;

	for (i = 0; i < 5; i++)
	{
		array[i] = i;
	}

	/*��������Ԫ�ص�ֵ��ָ��棩*/
	for (p = &array[0]; p != &array[5]; p++)
	{
		printf("%d ", *p);
	}
	printf("\n");
	/*��һ�ַ�ʽ���*/
	p = &array[0];
	for (i = 0; i < 5; i++)
	{
		printf("%d ", *(p + i));
	}
	printf("\n");
	/*���������������*/
	for (i = 0; i < 5; i++)
	{
		printf("%d ", i[array]);
	}
	printf("\n");
}
//��������
/*
�����������˼��
1.����Ҫ����������У��ҵ�һ���ʵ��Ļ�׼ֵ��pivot����
2.�������ң�������pivot������ݣ�
3.�������󣬼�����pivotС�����ݣ�
4.������������ܼ��������ݣ����ҵ������ݽ�����
5.�ظ�����2~4�Ĳ�����ֱ������ʼ�������±�ʹ��ҿ�ʼ�������±귢����ͻΪֹ��
*/
#define SWAP(a, b) {int temp; temp = a; a = b; b = temp;}
void exp_2_6_QuickSort_Code(int* data, int left, int right)
{
	int left_index = left;
	int right_index = right;
	int pivot = data[(left + right) / 2];

	while (left_index <= right_index)
	{
		for (; data[left_index] < pivot; left_index++);
		for (; data[right_index] > pivot; right_index--);
		if (left_index <= right_index)
		{
			SWAP(data[left_index], data[right_index]);
			left_index++;
			right_index--;
		}
	}
	if (right_index > left)
	{
		exp_2_6_QuickSort_Code(data, left, right_index);
	}
	if (left_index < right)
	{
		exp_2_6_QuickSort_Code(data, left_index, right);
	}
}
void exp_2_6_QuickSort_Test()
{
	int data[] = { 1,3,5,7,4,9,2 };
	exp_2_6_QuickSort_Code(data, 0, 6);
	for (int i = 0; i < 7; i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

