#include <stdio.h>

void Func_printf_placeholder()
{
}

void Func_printf_format_minwidth()
{
    int a = 123456;
    printf("a = %1d\n", a); // ָ����Ȳ���ʱ�� �����������ֱ���
    printf("a = %10d\n", a);

    printf("\n=== test fill with zero. ===\n");
    printf("a = %010dHHH\n", a);
    printf("a = %-10dHHH\n", a);
    printf("a = %-010dHHH\n", a);  // ��������£�0���ʧЧ
}

void Func_printf_format_sign()
{
    int a = 123;
    printf("a = %+d\n", a);
    printf("a = %+5d\n", a);
}

void Func_printf_format_alignment()
{
    int a = 123;
    printf("a = %-10dHHH\n", a);
}

void func_printf_format_limitDigits() {
	printf("%.2f\n", 1.2345); // 1.23

	// ����λ��ֻ����С�����λ������������Ч
	printf("%.2d\n", 12345); // 12345

	// ���� * �����޶�ֵ
	printf("%.*f\n", 2, 1.2345); // 1.23
	printf("%*.*f\n", 5, 2, 1.2345); // ' 1.23'
	printf("%+*.*f\n", 5, 2, 1.2345); // +1.23
}

int main(int argc, char const *argv[])
{
    // Func_printf_format_minwidth(); // ��С���
    // Func_printf_format_sign(); // ������
    // Func_printf_format_alignment(); // ���뷽ʽ
    func_printf_format_limitDigits(); // ���Ƹ�����λ��
    return 0;
}
