#include <stdio.h>

// �ַ���������ʼ��
// ���ַ�ʽ���Զ����ַ��������е�ÿ���ַ���ֵ�������е�ÿ��Ԫ�ء�
// ע�⣺��ʹ���ַ���������ʼ��ʱ������Ĵ�С������ڵ����ַ����ĳ��ȼ�1����Ϊ�ַ��������л�������һ��'\0'�ַ���
void CharInit1()
{
    char arr[] = "Hello World1";
    printf("%s, sizeof=%d\n", arr, sizeof(arr));  // 13

    // ָ���˳��ȵ�����£�Ҳ����������ֵ��ֵ
    char arr2[20] = "Hello World2";
    printf("%s, sizeof=%d\n", arr2, sizeof(arr2));  // 13

    // arr = arr2;
    // error: incompatible types in assignment of 'char [20]' to 'char [13]'
}

// �ַ������ʼ��
// ���ַ�ʽ��Ҫ�ֶ�ָ��ÿ��Ԫ�ص�ֵ�����һ��Ԫ�ر�����'\0'����ʾ�ַ����Ľ�����
void CharInit2()
{
    char arr[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '2', '\0'};
    printf("%s, sizeof=%d\n", arr, sizeof(arr));  // 13
}

// ���ֳ�ʼ��
// ���ַ�ʽֻ��ʼ���˲���Ԫ�أ�δ��ʼ����Ԫ�ػᱻ�Զ���ֵΪ0��
void CharInit3()
{
    char arr[13] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '3'};
    printf("%s, sizeof=%d\n", arr, sizeof(arr));  // 13
}

// ȫ����ʼ��
// ���ַ�ʽ�Ὣ�����е�����Ԫ�ض���ֵΪ0��
void CharInit4()
{
    char arr[13] = {0};
    printf("%s, sizeof=%d\n", arr, sizeof(arr));  // 13
}

int main(int argc, char const *argv[])
{
    CharInit1();
    CharInit2();
    CharInit3();
    CharInit4();
    return 0;
}
