#include <stdio.h>
#include <iostream>
#include "../Proj/BookNotes_Head.h"
using namespace std;

void heima_cpp_heap_area()
{
    int* p = new int(10);       //new ���ص��Ǹ����͵�ָ��
    int* arr = new int[10];     //10����������10��Ԫ�أ�����������׵�ַ
    delete[] arr;               //�ֶ��ͷ�����
    cout << p << endl;
}

void CSDN_douhaoyunsuanfu()
{
    int a = 1;
    int b = 2;
    int c = (a, b++, a += b);
    cout << c << endl;
}