#include "../Jx_���װ���.h"

//�ṹ�������û� �Զ�����������ͣ������û��洢��ͬ����������

//���� �ṹ��
//	struct �ṹ���� { �ṹ���Ա�б� } object_names��
//	`object_names` �Ǳ��������ƣ������Ͽ���ʡ��
struct Student
{
	//��Ա�б�
	string m_Name;
	int m_Age;
	int m_Score;
	string m_Hobby;
};

//��������ѧ��
// ��һ�֣�struct Student s1
// �ڶ��֣�struct Student s2 = {...}
// �����֣��ڴ����ṹ��ʱ�ʹ���һ���ṹ�����
void struct_Jx001()
{
	//��һ�֣�struct Student s1
	Student s1;
	s1.m_Name = "����";
	s1.m_Age = 18;
	s1.m_Score = 0;

	//�ڶ��֣�struct Student s2 = {...}
	Student s2 = { "����", 20, 10 };	//���Ǻ��Ƽ�
	
	//�����֣��ڴ����ṹ��ʱ�ʹ���һ���ṹ�����
	//	����s3�Ѿ��������ˣ�����ֱ�� s3 = {...};

	//�о�һ���ܷ�����
	s2 = { "����", 24, 60 };	//���������Ա�����
	s2 = { "����" };	//ֻ����һ�������أ�
	cout << s2.m_Name << " " << s2.m_Age << " " << s2.m_Score << " " << s2.m_Hobby << endl;	//���� 0 0 NULL
	s2 = {};	//����������Ϊ��
	cout << s2.m_Name << " " << s2.m_Age << " " << s2.m_Score << " " << s2.m_Hobby << endl;	//NULL 0 0 NULL
}