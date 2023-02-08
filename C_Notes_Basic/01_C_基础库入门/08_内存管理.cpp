#include <stdio.h>
#include "C_Basic_main.h"

#include <stdlib.h>
#include <string.h>

#pragma region Memory_voidָ��
void func_Memory_voidPoint() {
	int x = 10;
	void* p = &x; // ����ָ��תΪ void ָ��
	int* q2 = reinterpret_cast<int*>(p); // void ָ��תΪ����ָ��
	// or
	int* q1 = (int*)p;
}
#pragma endregion

#pragma region Memory_malloc
void func_Memory_malloc() {
	int* p = (int*)malloc(sizeof(int));
	// ���ֱ�Ӷ� p �����������⣬����Ҫ��ȷ���Ѿ�����ɹ�
	memset(p, 0, sizeof(int));
	if (p != NULL) *p = 12;
	printf("%d\n", *p); // 12
	free(p);
}

void func_Memory_calloc() {
	int* p = (int*)calloc(10, sizeof(int));
	free(p);
}
#pragma endregion
