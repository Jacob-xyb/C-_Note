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
//����Ȩ��
class PersonPermission
{
public:
	//����Ȩ��
	string mName;
protected:
	//����Ȩ��
	string mCar;
private:
	//˽��Ȩ��
	int mIdPassword;
public:
	void func()		//���ڿ��Է�������Ȩ��
	{
		this->mName = "Jx";
		this->mCar = "Porsche";
		this->mIdPassword = 666666;
	}
};
void Class_Permission()
{
	PersonPermission p1;
	p1.mName = "����";	//����ֻ�ܷ��ʹ���Ȩ��
}
//diff in struct and class
struct DiffInStruct
{
	int m_A;		//Ĭ��Ȩ��Ϊ����Ȩ��
};
class DiffInClass
{
	int m_A;		//Ĭ��Ȩ��Ϊ˽��Ȩ��
};
void Class_DiffInStructAndClass()
{
	DiffInStruct obj_1;
	obj_1.m_A = 100;	//struct ���Է���
	DiffInClass obj_2;
	//obj_2.m_A = 100;	//class �����Է���
}
//�Լ����Ƴ�Ա���ԵĶ�дȨ��
class PersonPermission01
{
public:
	//д����
	//�ַ�����ò�Ҫ�����ã�ֱ�������ַ���ʱ���޷������ô���
	void setName(string name) {this->mName = name;}
	//������
	string getName() {return this->mName;}
	//ֻ������
	int getAge() { this->mAge = 18; return this->mAge; }
	//ֻд����
	void setHobby(string hobby) { this->mHobby = hobby; }
private:
	string mName;		//�ɶ���д
	int mAge;			//ֻ��
	string mHobby;		//ֻд
};
void Class_Permission01()
{
	PersonPermission01 p1;
	p1.setName("����");
	cout << p1.getName()	<< endl;
	cout << p1.getAge()		<< endl;
	p1.setHobby("coding");
}

/*���캯������������*/
//�﷨
class PersonJx001
{
public:
	//���캯��
	PersonJx001()
	{
		cout << "���캯���ĵ���" << endl;
	}
	//��������
	~PersonJx001()
	{
		cout << "���������ĵ���" << endl;
	}
};
void Class_Jx002()
{
	PersonJx001 p1;
	cout << "this is a pause.." << endl;
}
//���캯���ķ���
void Class_Jx003()
{

}
