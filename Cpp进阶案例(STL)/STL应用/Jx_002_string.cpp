#include "Jx_test.h"

// string�Ĺ��캯��
//	`string();`		// ����һ���յ��ַ��� ���磺string str;
//	`string(const char* s); `		// ʹ���ַ���s��ʼ��
void string_001()
{
	string s1;	// Ĭ�Ϲ���
	const char* str = "hello world";		// C���Է���ַ���
	string s2(str);
	cout << "������ַ���Ϊ��" << s2 << endl;
}
//	`string(const string& str);`		// ʹ��һ��string�����ʼ����һ��string����
void string_002()
{	
	string str = "hello world";
	string s3(str);
	cout << "string��ʼ���Ķ���Ϊ��" << s3 << endl;
}