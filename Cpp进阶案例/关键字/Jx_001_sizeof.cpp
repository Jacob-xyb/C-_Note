#include "../Jx_���װ���.h"

//������sizeofӦ��
void sizeof_type001()
{
	//sizeof()���Է���һ��������ռ�ڴ��С
	//	����������������ָ����ʵ��sizeof()����
	int a[5] = { 1,2,3,4,5 };
	std::cout << "sizeof()ʵ��sizeof(a)��" << sizeof(a) << std::endl;
	int jx;		// �⽫��������ʵ�ֵĽ��
	//	--
	//	ž��һ�´��ԭ�Σ��мǲ�Ҫ��ʮ�����ƽ��мӼ�
	std::cout << "a: " << a << std::endl;			// int����ָ��
	std::cout << "a + 1: " << a + 1 << std::endl; 
	std::cout << "&a: " <<  &a << std::endl;		// ��һ������ָ��
	std::cout << "&a+1: " << &a + 1 << std::endl;
	std::cout << "&a - (&a + 1): " << &a - (&a + 1) << std::endl;
	//	--
	//jx = int(&a + 1) - int(&a);
	// ��ʵ���Ƕ���ָ�룺β��ַ-�׵�ַ
	std::cout << "Jxʵ��sizeof(a)��" << int(&a + 1) - int(&a) << std::endl;

	std::cout << "sizeof()ʵ��sizeof(a[0])��" << sizeof(a[0]) << std::endl;
	std::cout << "Jxʵ��sizeof(a[0])��" << int(a + 1) - int(a) << std::endl;

	//sizeof()������ֱ�Ӵ�ӡ�����������͵��ڴ�ռλ
	//std::cout << sizeof(int) << std::endl;
	//std::cout << sizeof(float) << std::endl;
}

//�鿴��ǰϵͳ������������ռ�ֽ�
void sizeof_view001()
{
	std::cout << "�鿴��ǰϵͳ������������ռ�ֽ�" << std::endl;
	std::cout << "sizeof(int): " << sizeof(int) << std::endl;
	std::cout << "sizeof(float): " << sizeof(float) << std::endl;
	std::cout << "sizeof(double): " << sizeof(double) << std::endl;
	std::cout << "sizeof(char): " << sizeof(char) << std::endl;
	std::cout << "sizeof(bool): " << sizeof(bool) << std::endl;
}

