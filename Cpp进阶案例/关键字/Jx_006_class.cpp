#include "../Jx_���װ���.h"

/*��װ*/
//��װһ���򵥵��ࣺԲ��
const double PI = 3.14;
class Circle
{
public:
	double m_R;		//�뾶
	double CirclePerimeter()
	{
		return 2 * PI * m_R;
	}
};
void Class_Jx001()
{
	//����һ�� Բ�� ����
	Circle c1;
	c1.m_R = 10;
	cout << "c1�ܳ�: " << c1.CirclePerimeter() << endl;
}
//��װһ������ͨ���ࣺѧ��
class Student
{
public:		//Ȩ��
	//����
	string mName;
	int mId;
	//��Ϊ
	void showStudent()
	{
		cout << "����: " << this->mName << endl;
		cout << "ѧ��: " << this->mId	<< endl;
	}
	//	��ֵ����
	void setName(string& name) { this->mName = name; }
	void setId(int id) { this->mId = id; }
};