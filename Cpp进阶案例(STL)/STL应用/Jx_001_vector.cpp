#include "Jx_test.h"
//#include <vector>
//#include <algorithm>

// vector�����ڴ��������������
void vector_001()
{
    //// ������һ��vector����������
    vector<int> v;

    //// �������в�������
    //// push_back()      // �� vector ��β������
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    // ͨ�����������������е�����
    // vector<int>::iterator  vector �������µ� ������
    vector<int>::iterator itBegin = v.begin();      // v.begin() ��ʼ��������ָ�������е�һ��Ԫ��
    vector<int>::iterator itEnd = v.end();      // v.end(); ������������ָ�����������һ��Ԫ�ص���һ��λ��
}

// vector �� ��һ�ֱ�����ʽ
void vector_002()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    vector<int>::iterator itBegin = v.begin();
    vector<int>::iterator itEnd = v.end();

    // ��һ��
    while (itBegin != itEnd)
    {
        cout << *itBegin << endl;
        itBegin++;
    }
}

// vector �� �ڶ��ֱ�����ʽ
void vector_003()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    for (vector<int>::iterator it = v.begin(); it != v.end();it++)
    {
        cout << *it << endl;
    }
}


void myPrint(int val)
{   
    cout << val << endl;
}

// vector �� �����ֱ�����ʽ
void vector_004()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    // ������ ����STL�ṩ�����㷨 <algorithm>
    for_each(v.begin(), v.end(), myPrint);      // �����˻ص�����
}

//vector �����д���Զ�����������
//  �����
class Person
{
public:
    Person(string name, int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    string m_Name;
    int m_Age;
};

void vector_005()
{
    vector<Person> v;
    Person p1("aa", 10);
    Person p2("bb", 20);
    Person p3("cc", 30);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        // *it �����ú���һ�� Person �������ͣ�����vector<>�ڵ�����
        cout << "������" << (*it).m_Name << endl;
        cout << "���䣺" << (*it).m_Age << endl;
        // �� it ��ָ��ʱ������ֱ����ָ�����������
        cout << "������" << it->m_Name << endl;
        cout << "���䣺" << it->m_Age << endl;
    }
}

//  ���ָ��
void vector_006()
{
    vector<Person*> v;      // Type* ����ָ�����˼
    Person p1("aa", 10);
    Person p2("bb", 20);
    Person p3("cc", 30);
    v.push_back(&p1);       // &����  ȡʵ���������ַ
    v.push_back(&p2);
    v.push_back(&p3);
    for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
    {
        // *it �����ú���һ�� Person* �������ͣ�����vector<>�ڵ�����
        cout << "������" << (*(*it)).m_Name << endl;
        cout << "���䣺" << (*(*it)).m_Age << endl;
        // ���ν�����Ҳ��������д
        cout << "������" << (**it).m_Name << endl;
        cout << "���䣺" << (**it).m_Age << endl;
        // �� *it ��ָ��ʱ������ֱ����ָ�����������
        cout << "������" << (*it)->m_Name << endl;
        cout << "���䣺" << (*it)->m_Age << endl;
    }
}


// ����Ƕ������
void vector_007()
{
    vector<vector<int>> v;
    // ����С����
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;
    // ��С�������������
    for (int i = 0; i < 4; i++)
    {
        v1.push_back(i+1);
        v2.push_back(i+2);
        v3.push_back(i+3);
        v4.push_back(i+4);
    }
    // ��С�������뵽��������
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    // ͨ����������������������
    for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++)
    {
        for (vector<int>::iterator jt = it->begin(); jt != it->end(); jt++)
        {
            cout << *jt << "\t";
        }
        cout << endl;
    }

}