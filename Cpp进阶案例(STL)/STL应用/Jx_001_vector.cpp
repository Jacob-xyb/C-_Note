                  #include "Jx_test.h"
//#include <vector>
//#include <algorithm>


// дһ����ӡvector<int>�ĺ����������
void printVector(vector<int>& v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}


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


// vector ���캯��
/*- `vector<T> v;`		// ����ģ��ʵ����ʵ�֣�Ĭ�Ϲ��캯��
- `vector(v.begin(),v.end());`		// ��v[ begin(),end() ) �����е�Ԫ�ؿ���������
- `vector(n, elem);`				// ���캯����n��elem����������
- `vector(const vector& vec);`		// �������캯��*/
void vector_008()
{
    // Ĭ�Ϲ��캯�����޲ι���
    vector<int> v1;     
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);        // �� v1 �������
    }
    printVector(v1);        // ��дһ�� print �����������

    // ���䷽ʽ����
    vector<int> v2(v1.begin(), v1.end());       
    printVector(v2);

    // n��elem��ʽ����
    vector<int> v3(10, 100);
    printVector(v3);

    // ��������
    vector<int> v4(v3);
    printVector(v4);
}


// vector ��ֵ����
/*- `vector& operator=(const vector& vec);`		// ���صȺŲ�����
- `assign(beg,end);`		// [beg,end) ���俽����ֵ
- `assign(n,elem);`		// n��elem������ֵ*/
void vector_009()
{
    vector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    // = ֱ�Ӹ�ֵ
    cout << "= ֱ�Ӹ�ֵ" << endl;
    vector<int> v2 = v1;
    printVector(v2);

    // ���俽������
    cout << "���俽������" << endl;
    v2.assign(v1.begin(), v1.end());
    printVector(v2);

    // n��elem������ֵ
    cout << "n��elem������ֵ" << endl;
    v2.assign(10, 10);
    printVector(v2);
}


// vector �����ʹ�С
/*- `empty();`			// �ж������Ƿ�Ϊ��
- `capacity();`			// ����������
- `size();`				// ����������Ԫ�صĸ���
- `resize(int num);`	// ���¶��������ĳ���Ϊnum,
  // ��������䳤������Ĭ��ֵ�����λ�á�
  // ���������̣���ĩβ�����������ȵ�Ԫ�ر�ɾ����
- `resize(int num, elem);`	// Ĭ��ֵ��Ϊ elem*/
void vector_010()
{
    vector<int> v1;
    cout << "����������empty() ����ֵΪ��" << v1.empty() << endl;
    cout << "������������Ϊ��" << v1.capacity() << endl;
    cout << "��������Ԫ�صĸ�����" << v1.size() << endl;

    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    cout << "�鿴һ�¸�ֵ������������" << endl;
    printVector(v1);

    // ���Է��֣������������������ĸ���Ҫ������Ϊvector���Զ������ռ�
    cout << "��ʱ��������empty() ����ֵΪ��" << v1.empty() << endl;
    cout << "����������Ϊ��" << v1.capacity() << endl;
    cout << "������Ԫ�صĸ�����" << v1.size() << endl;
    // ������Ԫ�ظ���Ϊ10��ʱ����������Ϊ13

    // ����һ�������ĳ���
    v1.resize(12);
    cout << endl << "Ԫ�ظ������䵽12ʱ��" << endl;
    cout << "�鿴һ�����������������" << endl;
    printVector(v1);
    cout << "��ʱ��������Ϊ��" << v1.capacity() << endl;
    cout << "��ʱ������Ԫ�صĸ���Ϊ��" << v1.size() << endl;
    // ��ʱ��������������13��˵��Ԫ�ظ�����������������ʱ������������������
    //      ��ô������С��
    cout << endl << "Ԫ�ظ�����С��6�������������б仯��" << endl;
    v1.resize(6);
    cout << "�鿴һ������������������" << endl;
    printVector(v1);
    cout << "��ʱ��������Ϊ��" << v1.capacity() << endl;
    cout << "��ʱ������Ԫ�صĸ���Ϊ��" << v1.size() << endl;
    //      ��..��������ʱ����Ҳ���ᷢ���仯��
    //      �������Ϊ���Ѿ���������ô��Ŀռ��ˣ����þͲ����ٸı���
    cout << endl << "��֤һ��`����==����`ʱ������" << endl;
    v1.resize(v1.capacity());
    cout << "��ʱ��������Ϊ��" << v1.capacity() << endl;
    cout << "��ʱ������Ԫ�صĸ���Ϊ��" << v1.size() << endl;
    //      ��֤������ռ乻�þͲ����ٸı�
    cout << endl << "��֤һ��`����==����+1`ʱ������" << endl;
    v1.resize(v1.capacity()+1);
    cout << "��ʱ��������Ϊ��" << v1.capacity() << endl;
    cout << "��ʱ������Ԫ�صĸ���Ϊ��" << v1.size() << endl;
    //      ��ʱ��������Ԫ�ظ���Ϊ14������Ϊ19
    //      ��֮����࿪�ٿռ䣬����ÿ�ζ࿪�ٶ������������Լ�������
}