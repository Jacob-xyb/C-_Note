#include <fstream>
#include <sstream> 
//#include "../Jx_���װ���.h"

/*
char buff[MAX_PATH];//���ڴ�Ż�ȡ��·����Ϣ��
GetModuleFileName(NULL,buff,MAX_PATH);//��һ������Ϊ�����NULL��ָ��ǰ���򡣵ڶ����������ڴ�ŵ�ַ��ָ�룬������������ϵͳ�Դ��ĺ궨�塣���ùܡ�
CString str=buff;//��buff��ŵ�·�������ַ���str,��ʱbuffֵ�磺��E:\MyTest\Debug\****.exe��
int pos=str.ReverseFind('\\');//���ҵ������һ����\\������
str=str.Left(pos+1);//strֻ��ȡexe�����ļ���·���� strΪ��"E:\MyTest\Debug\"
//ע�⣺������reversefind()������ʹ�õ��ǵ����š�
*/

std::string getExePath()
{
#ifdef WIN32
	char buffer[260];
	GetModuleFileName(NULL, (LPSTR)buffer, MAX_PATH); //��ȡ��ǰexe��·��
	string addr_profile = string(buffer);
	addr_profile = addr_profile.substr(0, addr_profile.rfind('\\'));

	subreplace(addr_profile, "\\", "/");//����/б��
	return addr_profile;
#else
#endif
}