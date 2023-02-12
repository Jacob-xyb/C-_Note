#include <stdio.h>
//#include "C_Basic_main.h"


#pragma region hello_world
void hello_world() {
	printf("hello world");
}
#pragma endregion

#pragma region printf
void func_printf_placeholder() {
	printf("%s says it is %i o'clock\n", "Ben", 21);
}
// ������
void func_printf_width() {
	// Ĭ���Ҷ��룬�ո����
	printf("%5d\n", 123);  // '  123'
	// �����
	printf("%-5d\n", 123); // '123  '

	printf("%12f\n", 123.45);  // '  123.450000'
	printf("%6f\n", 123.45);  // '123.450000'

	// ������ʾ������
	printf("%+d\n", 12); // ��� +12
	printf("%+d\n", -12); // ��� -12
}

void func_printf_width_test() {
	// ��ʾ�����ź�������Ⱥ�˳����Ի���
	printf("%+-5d\n", 123); // '+123  '
	printf("%-+5d\n", 123); // '+123  '
}
// �������λ��(����)
void func_printf_limit_digits() {
	printf("%.2f\n", 1.2345); // 1.23

	// ����λ��ֻ����С�����λ������������Ч
	printf("%.2d\n", 12345); // 12345

	// ���� * �����޶�ֵ
	printf("%.*f\n", 2, 1.2345); // 1.23
	printf("%*.*f\n", 5, 2, 1.2345); // ' 1.23'
	printf("%+*.*f\n", 5, 2, 1.2345); // +1.23
}
// ������Ƴ���(�ַ���)
void func_printf_limit_string() {
	// С���ַ�������ʱ�����ȡ���
	printf("%.5s\n", "hello world");	// hello
}

// �����������
void func_printf_BaseNumber() {
	int num = 100;

	//ʮ���� ��� %d %u %ld %lu
	printf("ʮ���ƣ�num=%d\n", num);//100
	//�˽��� ��� %o ��0��ͷ
	printf("�˽��ƣ�num=%o\n", num);//144
	//ʮ������ ��� %x ��0x��ͷ
	printf("ʮ�����ƣ�num=%x\n", num);//64

	// %��׷��# ������ʾ�����Ӧ���Ʊ�־��
	printf("�˽��ƣ�num=%#o\n", num);//0144
	printf("ʮ�����ƣ�num=%#x\n", num);//0x64

	//��ͬ���� ���������ݵı�����ʽ �����޸����ݱ���
}
#pragma endregion

#pragma region �����

void func_calculate_sign() {
	int a;
	a = 1;
	printf("%d\n", a++);  // 1
	a = 1;
	printf("%d\n", ++a);  // 2
}

void func_digital_calculate_sign() {
	printf("%d\n", ~1);
}

void func_digital_calculate_sign_JudgeRightShiftOperator() {
	char data = 0x80;
	printf("data:%d\n", data);
	if ((data >> 2) == (char)0x20)
	{
		printf("�߼�����");
	}
	else if ((data >> 2) == (char)0xe0)
	{
		printf("��������");
	}
	else {
		printf("%d", (data >> 2));
	}
}

void func_comma_calculate_sign() {
	int x;
	x = 1, 2, 3;
	// = �� , �и��ߵ����ȼ������� x=1
	printf("%d\n", x);  // 1

	// �����������ķ���ֵΪ���һ�����ʽ��ֵ
	int y;
	y = (x = 1, 2, 3);
	printf("%d\n", y);  // 3
}

#pragma endregion

