#include "Transfer.h"

std::string G_NAME = "Jacob-xyb";

void Call_OwnershipOperator() {
	std::string G_NAME = "��ϵͳ�����ľֲ�����";
	std::cout << "��ʽ�������ȵ��þֲ�����: " << G_NAME << std::endl;
	std::cout << "��ʽ����ȫ�ֱ���: " << ::G_NAME << std::endl;
}
