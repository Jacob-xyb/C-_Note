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
class PersonJx002
{
public:
	//�޲ι��캯��
	PersonJx002()
	{
		cout << "�޲ι��캯���ĵ���" << endl;
	}
	PersonJx002(int a)
	{
		this->mAge = a;
		cout << "�вι��캯���ĵ���" << endl;
	}

	//�������캯��
	PersonJx002(const PersonJx002& p)
	{
		mAge = p.mAge;
		cout << "�������캯���ĵ���" << endl;
	}
	
	//��������
	~PersonJx002()
	{
		cout << "����Ϊ " << mAge << " �Ķ�������" << endl;
	}

	int getAge() { return mAge; }
private:
	int mAge;
};
void Class_Jx003()
{
	//1.���ŷ�
	PersonJx002 p1;		//�����޲ι��캯��
	cout << p1.getAge() << endl;
	PersonJx002 p2(10);	//�����вι��캯��
	cout << p2.getAge() << endl;

	PersonJx002 p3(p2);	//���ÿ������캯��
	cout << p3.getAge() << endl;

	//2.��ʽ��
	PersonJx002 p4;		//PersonJx002 p4();	д�����󣬻���Ϊ��һ����������.
	PersonJx002 p5 = PersonJx002(20);
	PersonJx002 p6 = PersonJx002(p5);

	//ע������
	PersonJx002(30);		// ��������	�ص㣺��ǰ��ִ�н�����ϵͳ���������յ���������
	cout << "aaa" << endl;		// ���Է��ֻ��� 'aaa' ֮ǰ���й��������
	// ע�⣺��Ҫ���ÿ������캯����ʼ����������
	// ��Ϊ����������Ϊ PersonJx002(p6) �� PersonJx002 p6�������ض���
	// PersonJx002(p6);

	//3.��ʽת����
	PersonJx002 p7 = 40;	//�вι���
	PersonJx002 p8 = p7;	//��������
}
//��ǳ����
class PersonJx003
{
public:
	//�޲ι��캯��
	PersonJx003()
	{
		cout << "�޲ι��캯���ĵ���" << endl;
	}
	//�вι��캯��
	PersonJx003(int age, int height)
	{
		this->mAge = age;
		this->mHeight = new int(height);
		cout << "�вι��캯���ĵ���" << endl;
	}
	//�������д�������캯��	//Ĭ�Ͽ������캯����ǳ����
	PersonJx003(const PersonJx003& p)
	{
		this->mAge = p.mAge;
		this->mHeight = new int(*p.mHeight);
		cout << "�������캯���ĵ���" << endl;
	}
	~PersonJx003()
	{
		if (mHeight)
		{
			delete mHeight;
			mHeight = NULL;
		}
		cout << "���������ĵ���" << endl;
	}
public:
	int mAge;
	int *mHeight;	//�������ݴ���������
};
void Class_Jx004()
{
	PersonJx003 p1(18, 160);	//�вι���
	PersonJx003 p2(p1);			//�������캯������ʱ����ǳ��������
	cout << "p1������" << p1.mAge << endl;
}
//��ʼ���б�
class PersonJx004
{
public:
	//��ͳ��ʼ������
	/*PersonJx004(int a, int b, int c)
	{
		mA = a;
		mB = b;
		mC = c;
	}*/

	//��ʼ���б����޲ι��캯��
	PersonJx004():mA(10),mB(20),mC(30){}

	//�вι��캯��Ҳ�����ó�ʼ���б��д
	PersonJx004(int a, int b, int c):mA(a), mB(b), mC(c) {}
public:
	int mA;
	int mB;
	int mC;
};
void Class_Jx005()
{
	PersonJx004 p1;
	cout << p1.mA << "\t" << p1.mB << "\t" << p1.mC << endl;
	PersonJx004 p2(11, 22, 33);
	cout << p2.mA << "\t" << p2.mB << "\t" << p2.mC << endl;
}
//��̬��Ա�����;�̬��Ա����
class PersonJx005
{
public:
	//��̬��Ա����
	static void func()
	{
		cout << "��̬��Ա�����ĵ���" << endl;
		mA = 100;		//��̬��Ա�������Է��ʾ�̬��Ա����
		//mB = 200;		//��̬��Ա�������ܷ��ʷǾ�̬��Ա����

	}
	//��̬��Ա����
	static int mA;
	//�Ǿ�̬��Ա����
	int mB;
private:
	//��̬��Ա����Ҳ���з���Ȩ�޵�
	static void func2()
	{
		cout << "˽�еľ�̬��Ա�����ĵ���" << endl;
	}
};
//	��ʼ����̬��Ա����
int PersonJx005::mA = 0;
void Class_Jx006()
{
	//1.ͨ���������
	PersonJx005 p1;
	p1.func();

	//2.ͨ����������
	PersonJx005::func();
}
//thisָ�뷵�ر���	//��ʽ���
class PersonJx006
{
public:
	PersonJx006() {}	//����û������вι��캯����c++�����ṩĬ���޲ι��죬���ǻ��ṩĬ�Ͽ�������
	PersonJx006(int age)
	{
		this->mAge = age;
	}
	/*�޷���ֵ*/
	//void PersonAddAge(PersonJx006& p)
	//{
	//	this->mAge += p.mAge;
	//}
	/*���ض��������*/
	PersonJx006& PersonAddAge(PersonJx006& p)
	{
		this->mAge += p.mAge;
		//thisָ��ʵ�������󣬶�*this���ǽ����ã�Ҳ����ʵ����������
		return *this;
	}
	/*���ض���Ŀ���*/
	//PersonJx006 PersonAddAge(PersonJx006& p)
	//	��ʱ���ص�ʱ��ᴴ��һ���µĶ���ע������

	int mAge;
};
void Class_Jx007()
{
	PersonJx006 p1(10);
	PersonJx006 p2(18);
	p1.PersonAddAge(p2);	//������Ȼ�ǿ��Ե�
	cout << p1.mAge << endl;
	//����������ʽ��̣����õĺ����͵÷��ض�����
	p1.PersonAddAge(p2).PersonAddAge(p2).PersonAddAge(p2);
	cout << p1.mAge << endl;
}