#include "Transfer.h"



#pragma region ��ȡָ������ĳ��ȼ�����

int get_len_array1(int* a) {
	return _msize(a) / sizeof(int);
}

int get_len_array2(int* a) {
	return *(a - 4) / sizeof(int);
}

void Call_point_and_array() {
	int* p1 = new int[10];
	std::cout << get_len_array1(p1) << std::endl;
	std::cout << get_len_array2(p1) << std::endl;
	int p2[10];
	//std::cout << get_len_array1(p2) << std::endl;		// �˴�����
	std::cout << get_len_array2(p2) << std::endl;		// �����������޷���ȡ��ȷ���
	delete[] p1;
}

#pragma endregion





