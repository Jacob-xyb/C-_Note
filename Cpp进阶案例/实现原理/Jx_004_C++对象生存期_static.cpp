#include "../Jx_���װ���.h"

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

// ��ʼ���ྲ̬��Ա
int Dog::count = 0;

void static_object()
{
    Dog dog01("Sherry");
    Dog dog02("Henry");
    Dog::func();
    cout << "������ " << Dog::count << " ֻ����" << endl;

}