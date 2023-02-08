#include <stdio.h>
#include <stdbool.h>
//#include "C_Basic_main.h"

#pragma region DataType_Char
void func_DataType_Char() {
	// char ���;���һ���ֽڵ��������洢
	char c;
	c = 65;
	printf("%c", c);  // A
	c = 'A';
	printf("%d\n", c);  // 65

	// ���������ӷ�����
	printf("%d\n", c + c); // 130
}
// �ַ���������ʾ����
void func_DataType_Char_OtherRepresentation() {
	// ת��д������ʹ�ð˽��ƺ�ʮ�����Ʊ�ʾһ���ַ���
	char x;
	x = 'B';
	x = 66;
	x = '\102'; // �˽���
	x = '\x42'; // ʮ������
	printf("%c\n", x);
}
#pragma endregion

#pragma region DataType_Int
void func_DataType_Int() {
	/*16λ��-32,768 �� 32,767��
	  32λ��-2,147,483,648 �� 2,147,483,647��
	  64λ��-9,223,372,036,854,775,808 �� 9,223,372,036,854,775,807��	*/
	int a;

	// signed��unsigned
	// signed int ��ͬ�� int
	// unsigned ��һ���ô�, ͬ�����ȵ��ڴ��ܹ���ʾ���������ֵ��������һ��
	unsigned int b;
}
// ������������
void func_DataType_Int_Subtype() {
	/*short int����дΪshort����ռ�ÿռ䲻����int��һ��ռ��2���ֽڣ�������ΧΪ-32768��32767)��
	  long int����дΪlong����ռ�ÿռ䲻����int������Ϊ4���ֽڡ�
	  long long int����дΪlong long����ռ�ÿռ����long������Ϊ8���ֽڡ�*/

	  // C ��������ʡ��int�����Ա����������Ҳ����д������������
	short a;
	unsigned long b;
}
// �����ļ���ֵ
void func_DataType_Int_Limit() {
	// ��ʱ����Ҫ�鿴����ǰϵͳ��ͬ�������͵����ֵ����Сֵ��C ���Ե�ͷ�ļ� limits.h �ṩ����Ӧ�ĳ���
	/*Ϊ�˴���Ŀ���ֲ�ԣ���Ҫ֪��ĳ���������͵ļ���ֵʱ��Ӧ�þ���ʹ����Щ������
	SCHAR_MIN��SCHAR_MAX��signed char ����Сֵ�����ֵ��
	SHRT_MIN��SHRT_MAX��short ����Сֵ�����ֵ��
	INT_MIN��INT_MAX��int ����Сֵ�����ֵ��
	LONG_MIN��LONG_MAX��long ����Сֵ�����ֵ��
	LLONG_MIN��LLONG_MAX��long long ����Сֵ�����ֵ��
	UCHAR_MAX��unsigned char �����ֵ��
	USHRT_MAX��unsigned short �����ֵ��
	UINT_MAX��unsigned int �����ֵ��
	ULONG_MAX��unsigned long �����ֵ��
	ULLONG_MAX��unsigned long long �����ֵ��*/
}
// ����
void func_DataType_Int_NumberSystems() {
	int x;
	// �˽���ʹ��0��Ϊǰ׺������017��0377��
	x = 012;
	printf("%d\n", x);  // 10

	// ʮ������ʹ��0x��0X��Ϊǰ׺������0xf��0X10
	x = 0xf;
	printf("%d\n", x);  // 15

	// ��Щ������ʹ��0bǰ׺����ʾ���������������Ǳ�׼��
	x = 0b1010;
	printf("%d\n", x);  // 10

	/*printf()�Ľ������ռλ�����¡�
	%d��ʮ����������
	%o���˽���������
	%x��ʮ������������
	%#o����ʾǰ׺0�İ˽���������
	%#x����ʾǰ׺0x��ʮ������������
	%#X����ʾǰ׺0X��ʮ������������*/
	x = 100;
	printf("dec = %d\n", x); // 100
	printf("octal = %o\n", x); // 144
	printf("hex = %x\n", x); // 64
	printf("octal = %#o\n", x); // 0144
	printf("hex = %#x\n", x); // 0x64
	printf("hex = %#X\n", x); // 0X64
}
#pragma endregion

#pragma region DataType_Float
void func_DataType_Float() {
	// ��ν��������������ʹ�� m * be ����ʽ���洢һ����ֵ��m��С�����֣�b�ǻ�����ͨ����2����e��ָ�����֡�
	// float����ռ��4���ֽڣ�32λ��������8λ���ָ����ֵ�ͷ��ţ�ʣ��24λ���С����ֵ�ͷ��š�
	// float���������ܹ��ṩ��ʮ���Ƶģ�6λ��Ч���֣�ָ�����ֵķ�ΧΪ��ʮ���Ƶģ�-37��37������ֵ��ΧΪ10-37��1037��
	float f;
	f = 10.5;
	double d = 10.18;

	// double��ռ��8���ֽڣ�64λ���������ṩ13λ��Ч���֡�
	// long double��ͨ��ռ��16���ֽڡ�
}
// ������������ʾ����
void func_DataType_Float_OtherRepresentation() {
	float f;
	f = .5;
	printf("%f\n", f);
	f = .5e3;
	printf("%f\n", f);
}
#pragma endregion

#pragma region DataType_Bool
void func_DataType_Bool() {
	// ͷ�ļ�stdbool.h��������һ�����ͱ���bool�����Ҷ�����true����1��false����0��ֻҪ�������ͷ�ļ����Ϳ���ʹ���⼸���ؼ���
	bool flag = true;
}
#pragma endregion

#pragma region DataType_Literals
void func_DataType_Literals() {
	int x;
	x = 1;
	printf("%zu", sizeof(x));  // 4
	x = 1L;
	printf("%zu", sizeof(x));  // 4
	// Tips����Ȼ������������long int�����Ǵ洢ʱ���ǰ��������ʹ洢��
}
#pragma endregion

#pragma region DataType_Overflow
void func_DataType_Overflow() {
	unsigned char x = 255;
	x = x + 1;
	printf("%d\n", x); // 0
}
#pragma endregion

#pragma region DataType_sizeof
void func_DataType_sizeof() {
	// ����Ϊ��������
	int x = sizeof(int);
	// ����Ϊ����
	int i;
	sizeof(i);
	// ����Ϊ��ֵ
	sizeof(3.14);
}
#pragma endregion

#pragma region DataType_AutoConversion
// ��ֵ���㷢�����Զ�ת��
void func_DataType_AutoConversion_Assignment() {
	// 1.��������ֵ����������
	// ++ ������������������ʱ��C ����ֱ�Ӷ���С�����֣��������������롣
	int x1 = 3.14;
	printf("%d\n", x1); // 3
}
// ������͵�����
void func_DataType_AutoConversion_MixedCalculation() {
	// signed �� unsigned �Ƚ�ʱ���Ὣ signed ת��Ϊ unsigned
	int a = -5;
	unsigned b = 4;
	if (a < b)
	{
		printf("a < b");
	}
	else
	{
		printf("a >= b"); // ���������
	}
}
#pragma endregion
