#include "../Jx_���װ���.h"

/*����ģ��*/
//ͨ����������
template<typename T>
void mySwap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
void Template_Type_001()
{
	/*���ַ�ʽʹ��ģ�庯��*/
	int a = 10;
	int b = 80;
	//1.�Զ������Ƶ�
	mySwap(a, b);
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	//2.��ʽָ������
	mySwap<int>(a, b);
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
}
//����ģ��ע������
template<typename T>
void Template_Func_002()
{
	cout << "func ����" << endl;
}
void Template_Type_002()
{
	//Template_Func_002();		//error:δ��Ϊ��T���Ƶ� ģ�� ����
	Template_Func_002<int>();	//������ʾָ�����;Ϳ���ʹ��
}
//����ģ�尸��
template<typename T>
void mySort_001(T arr[])
{
	int n = sizeof(arr)/sizeof(arr[0]);
	for (int i = 0; i < n; i++)
	{
		int minIdx = i;
		for (int j = i+1; j < n; j++)
		{
			if (arr[j] < arr[minIdx])
			{
				minIdx = j;
			}
		}
		if (minIdx != i)
		{
			mySwap(arr[i], arr[minIdx]);
		}
	}
}
void Template_Eg_001()
{
	char arr1[] = "dabiadao";
	mySort_001(arr1);
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
	{
		cout << arr1[i] << " ";
	}
	cout << endl;
}
//��ͨ�����뺯��ģ��
int myAdd_001(int a, int b)
{
	return a + b;
}
template<typename T>
int myAdd_002(T a, T b)
{
	return a + b;
}
//	��ͨ�������Է�����ʽ����ת��
void Template_Type_003()
{
	int a = 10;
	int b = 20;
	char c = 'c';
	cout << "a+b��" << myAdd_001(a, b) << endl;	//30
	/*��ͨ����*/
	//��ʽ����ת����a -- ASCII(97);c -- ASCII(99)
	cout << "a+c��" << myAdd_001(a, c) << endl;	//109
	/*ģ�庯��*/
	//�Զ������Ƶ�
	//cout << myAdd_002(a, c) << endl;	//error:������ƥ��
	//��ʽָ������
	cout << myAdd_002<int>(a, c) << endl;		//109
}
//���ù���
void myFuncPrint(int a, int b)
{
	cout << "���õ���ͨ����" << endl;
}
template<typename T>
void myFuncPrint(T a, T b)
{
	cout << "���õĺ���ģ��" << endl;
}
template<typename T>
void myFuncPrint(T a, T b, T c)
{
	cout << "���غ���ģ��" << endl;
}
void myFuncPrint_test001()
{
	int a = 0, b = 0;
	//1.���ȵ�����ͨ����
	myFuncPrint(a, b);
	//	�����ͨ����ֻ������û��ʵ�֣�Ҳ����ȥִ�к���ģ�壬������������ִ����ͨ����Ȼ�󱨴�error��1���޷��������ⲿ����
	//2.ͨ����ģ������б�ǿ�Ƶ��ú���ģ��
	myFuncPrint<>(a, b);
	//3.����ģ����Է�����������
	myFuncPrint(a, b, 100);
	//4.�������ģ����Բ������õ�ƥ�䣬���ȵ��ú���ģ��
	char c1 = 'a';
	char c2 = 'b';
	myFuncPrint(c1, c2);	//�Ƶ�������ʽת�������ȵ��ú���ģ��
}
//ģ�������	//ģ�庯������
struct PersonTest001
{
	string m_Name;
	int m_Age;
};
template<typename T>
bool myCompare001(T& a, T& b)
{
	return (a == b);
}
// ���þ��廯Person�İ汾ʵ�ִ��룬���廯�ᱻ���ȵ���
template<> 
bool myCompare001(PersonTest001& p1, PersonTest001& p2)
{
	return (p1.m_Name == p2.m_Name && p1.m_Age == p2.m_Age);
}
void Template_Type_004()
{
	//�������ú���ģ��
	int a = 10, b = 20;
	cout << myCompare001(a, b) << endl;
	//���廯����ģ��
	PersonTest001 p1 = { "Tom", 10 };
	PersonTest001 p2 = { "Tom", 10 };
	cout << myCompare001(p1, p2) << endl;
}


/*��ģ��*/
//��ģ���﷨
template<class NameT, class AgeT>
class PersonClass
{
public:
	PersonClass(NameT name, AgeT age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}
	NameT m_Name;
	AgeT m_Age;
};
void ClassTemplate_001()
{
	//��ģ�����Ҫʹ��ģ������б�
	PersonClass<string, int> p1("����", 18);
}
//��ģ���뺯��ģ�������
void ClassTemplate_002()
{
	//1.ֻ������ʽָ������
	PersonClass<string, int> p1("����", 18);
	//
}