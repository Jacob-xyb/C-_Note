#include <stdio.h>

void Func_d_print_char()
{
    char x1 = 128; // ��ȡ����: 1000 0000
    char x2 = 128; // ��ȡ����: 1000 0000
    // ֱ�����ڴ�����ӣ�
    // ++   1111 1111 1111 1111 1111 1111 1000 0000
    // ++  +1111 1111 1111 1111 1111 1111 1000 0000
    // ++  =1111 1111 1111 1111 1111 1111 0000 0000
    // ԭ��  1000 0000 0000 0000 0000 0001 0000 0000
    printf("%d\n", x1 + x2); // -256

    char x3 = x1 + x2;
    // �� char ����:
    // �����Ĳ���: 1111 1111 1111 1111 1111 1111 0000 0000
    // �����ȡ: 0000 0000
    // ԭ�����: 0000 0000
    printf("%d\n", x3); // 0
}

void Func_d_print_char_examples()
{
    char ch;
    ch = 128;
    printf("char(128)=\t%d\n", ch); // -128
    ch = -128;
    printf("char(-128)=\t%d\n", ch); // -128
}

int main(int argc, char const *argv[])
{
    Func_d_print_char_examples();
    return 0;
}
