#include <stdio.h>

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

int main(int argc, char const *argv[])
{
    scanf_error_format();
    return 0;
}
