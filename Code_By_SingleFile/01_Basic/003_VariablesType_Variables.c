#include <stdio.h>

int number = 100;

void Variables_not_init();

int main(int argc, char const *argv[])
{
    Variables_not_init();

    int number = 99;
    printf("number=%d\n", number);   // 99; �ֲ�������ȫ�ֱ���������ͬʱ��ȡ��ԭ�򣬾ֲ���������
    printf("number=%d\n", ::number); // 100; :: ��ʾȫ��������

    return 0;
}

void Variables_not_init()
{
    printf("++ Variables_not_init ++\n");
    // ����һ��Ҫ��ʼ��
    int a, b, c, d, e, f;

    printf("%d, %d, %d, %d, %d, %d\n", a, b, c, d, e, f); // ���������ֵ
    // ĳһ�����н��: 0, 16, 0, 7684384, 0, 122

    printf("++ Variables_not_init End ++\n\n");
}