#include <stdio.h>
#include "C_Basic_main.h"

struct fraction {
	int numerator;
	int denominator;
};

void func_Struct_Intro() {
	// ��ʽ1
	struct fraction f1;
	f1.numerator = 22;
	f1.denominator = 7;

	// ��ʽ2
	struct fraction f2 = { 22, 7 };

	// ��ʽ3 (c++20)
	//struct fraction f3 = { .numerator = 22 };
}

typedef struct cell_phone {
	int cell_no;
	float minutes_of_charge;
} phone;

void func_Struct_typedef() {
	phone p = { 1, 1.234 };
}

struct foo1 {
	char c;
	int a;
	char* b;
};

struct foo2 {
	char c;
	int a;
	char* b;
	char* d;
};

struct foo3 {
	int a;
	char* b;
	char c;
};

void func_Struct_Size() {
	printf("%zu\n", sizeof(struct foo1)); // 16
	printf("%zu\n", sizeof(struct foo2)); // 24
	printf("%zu\n", sizeof(struct foo3)); // 24
}

void func_Struct_Copy() {
	// struct ��������ʹ�ø�ֵ�������=�������Ƹ���һ����������ʱ������һ��ȫ�µĸ�����
	struct fraction f1 = { 1, 2 };
	struct fraction f2;
	f2 = f1;
	printf("%d-%d", f2.numerator, f2.denominator);
}
