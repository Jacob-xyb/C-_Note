#include "01_C_�����ⰸ��.h"

// ��֪������ �뾶r
// �㷨�� ��� S = ��*r*r

// �������裺
// ++ r ͨ�� ��������
// ++ ����һ��������� area = pai * r * r

#define PI 3.14

void Case_Calculate_Area_of_Circle() {

	float r = 0.0f;
	float s = 0.0f;		// Բ�����

	printf("������Բ�İ뾶r��");
	scanf("%f", &r);

	s = PI * r * r;

	printf("�뾶Ϊ��%f, ���Ϊ��%.2f ��Բ", r, s);
}
