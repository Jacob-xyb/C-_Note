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
//��ָ����ʳ�Ա����
class PersonJx007
{
public:
	void showPersonClass()
	{
		cout << "This is Person class!" << endl;
	}
	void showPersonAge()
	{
		//���һ���ж�
		if (this == NULL)
		{
			return;
		}
		cout << "age = " << m_Age << endl;
	}
	int m_Age;
};
void Class_Jx008()
{
	PersonJx007* p = NULL;		//����һ����Ŀ�ָ��
	p->showPersonClass();		//������������
	//p->showPersonAge();		//�������쳣: ��ȡ����Ȩ�޳�ͻ��
								//**this** �� nullptr��
	//�����ԭ���ǿ�ָ���޷��������ԣ���Ϊ thisָ��Ϊ�ա�
	//����������ж�
	p->showPersonAge();			//�����Ͳ��ᱨ����

	//���Կն���
	PersonJx007 p1;
	//�ն����������������
	p1.showPersonClass();
	p1.showPersonAge();
}
//���еĳ������ͳ�����
class PersonJx008
{
public:
	//�ڳ�Ա��������� const�����ε���thisָ�룬
	//	thisָ��ı��� ��ָ�볣�� ָ��ָ�򲻿����޸�	
	void showPerson() const
	{
		//��ʱָ��ָ���ֵҲ�������޸�
		//this->m_A = 100;

		//mutable �����ڳ�������Ҳ�����޸�
		m_B = 20;
		cout << "�������ĵ���" << endl;
	}

	void func(){}

	int m_A;
	//�����Ҫ�ڳ�������Ҳ�����޸ģ��ڱ���ǰ�� mutable
	mutable int m_B;
};
void Class_Jx009()
{
	const PersonJx008 p;	//�ڶ���ǰ��const����Ϊ������
	//p.m_A = 100;			//���������޸���ͨ�ĳ�Ա����
	p.m_B = 18;				//���ǳ���������޸� mutable ��Ա����
	p.showPerson();			//������ֻ�ܵ��ó�����
	cout << p.m_B << endl;
	//p.func()				//error:�����в����ݵ������޶���	
}


/*��Ԫ*/
//ȫ�ֺ�������Ԫ
class BuildJx001;
class ClassGoodGay001;
class BuildJx001
{
	//GoodGayȫ�ֺ�����friend����	//������������д��public��������
	friend void func_GoodGay(BuildJx001* build);
	//GoodGay��Ҳ��ͬ���ķ�ʽ����
	friend class ClassGoodGay;
	//��ĳ�Ա������������	//TODO������ǰ��˳��û�н��壬��������д���ǻᱨ��
	//friend void ClassGoodGay001::visit();
public:
	BuildJx001();

public:
	string m_LivingRoom;		//����
private:
	string m_BedRoom;			//����
};
BuildJx001::BuildJx001()
{
	m_LivingRoom = "����";
	m_BedRoom = "����";
}
//	ȫ�ֺ���
void func_GoodGay(BuildJx001* build)
{
	cout << "ȫ�ֺ������ڷ��ʣ� " << build->m_LivingRoom << endl;
	//cout << "ȫ�ֺ������ڷ��ʣ� " << build->m_BedRoom << endl;	//˽�����Բ��ɷ���

	//��������friend����ȫ�ֺ����󼴿ɷ�������˽�б���
	cout << "ȫ�ֺ������ڷ��ʣ� " << build->m_BedRoom << endl;
}
void Class_Jx010()
{
	BuildJx001 build;
	func_GoodGay(&build);
}
//������Ԫ
class ClassGoodGay
{
public:
	ClassGoodGay();
public:

	void visit();	//���� BuildJx001 ���е�����

	BuildJx001* build;
};
ClassGoodGay::ClassGoodGay()
{
	//����һ������
	build = new BuildJx001;		//new���󷵻�ָ��
}
void ClassGoodGay::visit()
{
	cout << "�û��������ڷ��ʣ� " << build->m_LivingRoom << endl;
	cout << "�û��������ڷ��ʣ� " << build->m_BedRoom << endl;
}
//	test
void Class_Jx011()
{
	ClassGoodGay gp;		//����һ����
	gp.visit();
}
//��Ա��������Ԫ
class ClassGoodGay001
{
public:
	ClassGoodGay001();
	void visit();		//	��visit�������Է���˽�г�Ա
	void visit2();		//	��visit2���������Է���˽�г�Ա

private:
	BuildJx001* build;

};
ClassGoodGay001::ClassGoodGay001()
{  
	build = new BuildJx001;
}
void ClassGoodGay001::visit()
{
	cout << "�û��������ڷ��ʣ� " << build->m_LivingRoom << endl;
	//cout << "�û��������ڷ��ʣ� " << build->m_BedRoom << endl;
}
void ClassGoodGay001::visit2()
{
	cout << "�û��������ڷ��ʣ� " << build->m_LivingRoom << endl;
	//cout << "�û��������ڷ��ʣ� " << build->m_BedRoom << endl;	//visit2���ɷ���
}
//	test
//void Class_Jx012()
//{
//	ClassGoodGay001 gp;
//	gp.visit();
//}


/*���������*/
//�Ӻ����������
class PersonJx009
{
public:
	PersonJx009& operator+(PersonJx009& p)
	{
		PersonJx009 temp;
		temp.mA = p.mA + this->mA;
		temp.mB = p.mB + this->mB;
		return temp;
	}
public:
	int mA;
	int mB;
private:
};
//	��Ա��������
void Class_Operator001()
{
	PersonJx009 p1;
	p1.mA = 10;
	p1.mB = 100;
	PersonJx009 p2;
	p2.mA = 20;
	p2.mB = 200;
	PersonJx009 p3;
	p3 = p1 + p2;		//���������+
	cout << p3.mA << " " << p3.mB << endl;
}
//	ȫ�ֺ�������
class PersonJx010
{
public:
	int mA;
	int mB;
private:
};
PersonJx010& operator+(PersonJx010& p1, PersonJx010& p2)
{
	PersonJx010 temp;
	temp.mA = p1.mA + p2.mA;
	temp.mB = p1.mB + p2.mB;
	return temp;
}
void Class_Operator002()
{
	PersonJx010 p1;
	p1.mA = 10;
	p1.mB = 100;
	PersonJx010 p2;
	p2.mA = 20;
	p2.mB = 200;
	PersonJx010 p3;
	p3 = p1 + p2;		//���������+
	cout << p3.mA << " " << p3.mB << endl;
}
//�������������
class PersonJx011
{
	//����ȫ�ֺ�������Ԫ����˽������
	friend ostream& operator<<(ostream& cout, PersonJx011& p);
public:
	PersonJx011(int a, int b);

	//ͨ���������ó�Ա�������� ����������� ��Ϊ�޷�ʵ�� cout �����
	//void operator<< (PersonJx011& p);
private:
	int mA;
	int mB;
};
PersonJx011::PersonJx011(int a, int b)
{
	this->mA = a;
	this->mB = b;
}
//	ֻ������ȫ�ֺ����������������
ostream& operator<<(ostream& cout, PersonJx011& p)
{
	cout << p.mA << " " << p.mB;
	//����ע����ʽ���˼��
	return cout;
}
void Class_Operator003()
{
	PersonJx011 p(10, 20);
	cout << p << endl;
}
//�������������
class MyInteger
{
public:
	MyInteger();
	int getNum();

	//����ǰ��++�����	//����ֵ�Ļ��ظ����þͻ��������
	MyInteger& operator++()
	{
		mNum++;
		return *this;
	}
	//���غ���++�����	//int����ռλ������������������ǰ�úͺ��õ�����ֻ��int��
	MyInteger operator++(int)
	{
		//�� ��¼��ʱ���
		MyInteger temp = *this;
		//�� ����
		mNum++;
		//���ص��Ǿֲ�������˲��ܷ�������
		return temp;
	}
private:
	int mNum;
};
MyInteger::MyInteger()
{
	this->mNum = 0;
}
int MyInteger::getNum()
{
	return this->mNum;
}
//	���������������ӡ���
ostream& operator<<(ostream& cout, MyInteger myint)
{
	cout << myint.getNum();
	return cout;
}
void Class_Operator004()
{
	MyInteger myint;
	cout << ++myint << endl;
	MyInteger myint2;
	cout << myint2++ << endl;
}
//��ֵ���������
class PersonJx012
{
public:
	PersonJx012(int age);
	~PersonJx012();

	//ǳ�������ظ��ͷŶ����ڴ�
	PersonJx012& operator=(PersonJx012& p);

	int* getAge();
private:
	int* mAge;
};
PersonJx012::PersonJx012(int age)
{
	mAge = new int(age);
}
PersonJx012::~PersonJx012()
{
	if (mAge!=NULL)
	{
		delete mAge;
		mAge = NULL;
	}
}
//	��Ҫ������ʽ���
//void PersonJx012::operator=(PersonJx012& p)
PersonJx012& PersonJx012::operator=(PersonJx012& p)
{
	/*�������ṩ��ǳ����*/
	//mAge = p.mAge;

	/*Ϊ�˱�������ظ��ͷţ�Ӧ�öԸ�ֵ�����������������*/
	//���ж��Ƿ��������ڶ�������������ͷŸɾ�
	if (mAge!=NULL)
	{
		delete mAge;
		mAge = NULL;
	}
	//Ȼ��������
	this->mAge = new int(*p.getAge());
	return *this;
}
int* PersonJx012::getAge() { return mAge; }
void Class_Operator005()
{
	PersonJx012 p1(18);
	PersonJx012 p2(20);

	p2 = p1;	//��ֵ����

	cout << *p1.getAge() << endl;
	cout << *p2.getAge() << endl;
}
//��ϵ���������
class PersonJx013
{
public:
	PersonJx013(string name, int age);

	bool operator==(PersonJx013& p);
	bool operator!=(PersonJx013& p);

	string getName() { return mName; }
	int getAge() { return mAge; }
private:
	string mName;
	int mAge;
};
PersonJx013::PersonJx013(string name, int age)
{
	mName = name;
	mAge = age;
}
bool PersonJx013::operator==(PersonJx013& p)
{
	if (mName == p.getName() && mAge == p.getAge())
	{
		return true;
	}
	return false;
}
bool PersonJx013::operator!=(PersonJx013& p)
{
	if (mName == p.getName() && mAge == p.getAge())
	{
		return false;
	}
	return true;
}
void Class_Operator006()
{
	PersonJx013 p1("zhangsan", 18);
	PersonJx013 p2("zhangsan", 18);
	if (p1==p2)
	{
		cout << "p1��p2����ȵ�" << endl;
	}
	else { cout << "p1��p2�ǲ���ȵ�" << endl; }
}
//�����������������
class MyPrint
{
public:
	//����ʹ�������������ĵ��ã���˱���Ϊ�º���
	void operator()(string test);

private:

};
void MyPrint::operator()(string test)
{
	cout << test << endl;
}
void Class_Operator007()
{
	MyPrint p;
	p("hello world");

	//��������д��
	MyPrint()("��������ʽ����");
}