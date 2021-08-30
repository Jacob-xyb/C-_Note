#include "../Jx_���װ���.h"

/*��̬����*/
class Dog
{
public:
    Dog(string name)
    {
        m_name = name;
        count ++;
    }

    static void func()
    {   
        count = 0;
        // ��̬���� ֻ�ܵ��� ��̬����
        // m_name = "Sunshine";
        cout << "static void func ����" << endl;
    }
    static int count;
private:
    string m_name;
};

//��ʼ���ྲ̬��Ա
int Dog::count = 0;

void static_object_001()
{
    Dog dog01("Sherry");
    Dog dog02("Henry");
    Dog::func();
    cout << "������ " << Dog::count << " ֻ����" << endl;
}

/*��������*/
//ȫ����   //ȫ�ֱ�������̬����������  //��������ǰ
int global_a = 1;           //ȫ�ֱ���
int global_b = 1;           //ȫ�ֱ���
const int CstG_a = 1;       //const���ε�ȫ�ֱ��� - ȫ�ֳ���
const int CstG_b = 1;       //const���ε�ȫ�ֱ��� - ȫ�ֳ���
void ParamType_001()
{
    //�ֲ�����
    int a = 1;
    int b = 1;

    //��̬����
    static int static_a = 1;
    static int static_b = 1;

    //����
    //  �ַ�������
    cout << "�ַ��������ĵ�ַ��\t\t" << (int)&"hello" << endl;
    //  const���εı���
    //      const���ε�ȫ�ֱ��� - ȫ�ֳ���
    //      const���εľֲ����� - �ֲ�����
    const int Cst_a = 1;
    const int Cst_b = 1;

    //���
    cout << "ȫ�ֱ��� global_a ��ַ��\t" << (int)&global_a << endl;
    cout << "ȫ�ֱ��� global_b ��ַ��\t" << (int)&global_b << endl;
    cout << "�ֲ����� a ��ַ��\t\t" << (int)&a << endl;
    cout << "�ֲ����� b ��ַ��\t\t" << (int)&b << endl;
    cout << "��̬���� static_a ��ַ��\t" << (int)&static_a << endl;
    cout << "��̬���� static_b ��ַ��\t" << (int)&static_b << endl;
    cout << "ȫ�ֳ��� CstG_a ��ַ��\t\t" << (int)&CstG_a << endl;
    cout << "ȫ�ֳ��� CstG_b ��ַ��\t\t" << (int)&CstG_b << endl;
    cout << "�ֲ����� Cst_a ��ַ��\t\t" << (int)&Cst_a << endl;
    cout << "�ֲ����� Cst_b ��ַ��\t\t" << (int)&Cst_b << endl;

    //�ܽ�:�ֲ�����ȫ����������(ȫ�ֱ�������̬����������)����ȫ����
}

//ջ��    //��ź����Ĳ���ֵ���ֲ�������
int* func_Stack_001()
{
    int a = 10; //�ֲ�����  //�����ջ����ջ���������ں���ִ������Զ��ͷ�
    return &a;
}
void Stack_001()
{
    /*ע������*/
    //  ��Ҫ���ؾֲ������ĵ�ַ
    int* p = func_Stack_001();
    cout << *p << endl;     //�ܹ��������10����Ϊ���������˱���
}