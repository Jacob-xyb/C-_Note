#include <stdio.h>
#include "C_Basic_main.h"

union quantity {
	short count;
	float weight;
	float volume;
};

void func_union_Intro() {
	union quantity q1;
	q1.count = 4;

	printf("count is %i\n", q1.count); // count is 4
	printf("weight is %f\n", q1.weight); // weight is δ����

	//union quantity q2 = { .count = 4 };

	union quantity q3 = { 4 };
	q3.volume = 8;
	printf("count is %i\n", q3.count); // count is 0
	printf("weight is %f\n", q3.weight); // weight is 8
	// ͬʱֻ����һ�����Դ��ڣ����渳ֵ�Ḳ��ǰ���
}