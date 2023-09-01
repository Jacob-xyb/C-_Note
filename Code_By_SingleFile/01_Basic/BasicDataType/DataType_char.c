#include <stdio.h>
#include <stdlib.h>

void char_assignment()
{
    // \nn: 字符的八进制写法
    // \xnn: 字符的十六进制写法
    int c_a = 0x61;
    printf("c_a = %c\n", c_a);

    printf("\\111 = \111\n");   // '\111' === 'I' === 74
    printf("\\x61 = \x61\n");   // '\x61' === 'a' === 97
    printf("%d", '\111' == 73); // 1
}

/// @brief 用整数赋值
void char_assigned_by_int()
{
    char x1 = 300;
    // 300 超出了char类型的取值范围，则char类型变量被截断为其取值范围内的值
    //++ 300: 0001 0010 1100
    // 截取后:      0010 1100
    // 打印输出 44
    printf("x1 = %d\n", x1);

    char x2 = -300;
    // -300 超出了char类型的取值范围，则char类型变量被截断为其取值范围内的值
    //++ -300原码: 1000 0000 0000 0000 0000 0001 0010 1100
    //++ -300反码: 1111 1111 1111 1111 1111 1110 1101 0011
    //++ -300补码: 1111 1111 1111 1111 1111 1110 1101 0100
    //++ 截取: 1101 0100
    //++ 整形提升后的补码: 1111 1111 1111 1111 1111 1111 1101 0100
    //++ 反码:            1111 1111 1111 1111 1111 1111 1101 0011
    //++ 原码:     1000 0000 0000 0000 0000 0000 0010 1100
    //打印输出: -44
    printf("x2 = %d\n", x2);
}

int main(int argc, char const *argv[])
{
    // char_assigned_by_int();

    char x = 'A';
    char c = x;
    printf("%c, size=%d", c, sizeof c);

    return EXIT_SUCCESS;
}
