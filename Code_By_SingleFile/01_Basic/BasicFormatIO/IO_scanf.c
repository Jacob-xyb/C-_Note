#include <stdio.h>

// ���ո���ַ���
void scanf_test_space2();

void scanf_error_format();

void scanf_test_n()
{
    char arr1[40], arr2[40];
    scanf("%s", arr1);
    scanf("%s", arr2);
    printf("arr1=%s,arr2=%s\n", arr1, arr2);

    char ch1;
    getchar(); // ���û�д˺��� �� chֱ�ӱ���ֵ '\n'
    scanf("%c", &ch1);
    printf("ch1=%c", ch1);
    return;
}

void scanf_test_space()
{
    int a, b, c;
    // - ������벻������д Error: %d%d%d
    // - %d %d; ������ʱӦ���Կո�����
    scanf("%d %d %d", &a, &b, &c);
    printf("%d,%d,%d", a, b, c);

    int x1;
    scanf("%d", x1);  // ���� '11 22' �ᱨ���޷�����
    printf("%d", x1);
}


int main(int argc, char const *argv[])
{
    // scanf_test_n();
    // scanf_test_space();
    scanf_test_space2();
    return 0;
}

void scanf_test_space2()
{
    // scanf ԭ���������ܽ��մ��пո���ַ���
    char s1[64], s2[64];
    scanf("%s", s1);   // ���� 'h1 h2', s1 ����յ� 'h1'
    scanf("%s", s2);   // s2 ��ֱ�Ӷ�ȡ�������� 'h2'
    printf("%s and %s", s1, s2);
}

void scanf_error_format()
{
    int a;
    printf("please input:");
    scanf("%d", &a);
    printf("result = %d\n", a);

    // û�б�scanf���յ��ַ�����Ȼ�洢�ڻ��������ȴ��´α����á�
    char str[20];
    scanf("%s", str);
    printf("%s", str);

    // 1.1 => 1
    // 2d => 2
}