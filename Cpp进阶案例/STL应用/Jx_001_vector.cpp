#include "../Jx_test.h"
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
// дһ����ӡvector<vector<int>>�ĺ����������

void printVector(vector<vector<int>>& v)
{
    for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++)
    {
        for (vector<int>::iterator jt = it->begin(); jt != it->end(); jt++)
        {
            cout << *jt << " ";
        }
        cout << endl;
    }
}

// ����һ��һά����������ӡ����
void init_Dim1andCout(vector<int>& v)
{
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    cout << "�鿴һ�´�����vector����" << endl;
    printVector(v);
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

    // n��elem��ʽ����   //`vector(n, elem);`
    vector<int> v3(10, 100);
    printVector(v3);
    //  elem��д���ᱨ��elem�ᱻ��ʼ��Ϊ0  //Jx_star
    vector<int> v5(10);
    cout << "v5������" << v5.capacity() << endl;
    printVector(v5);

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
    init_Dim1andCout(v1);

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

    // v1����ֱ�Ӹ�ֵ
    v1 = v2;
    cout << "����v1��ֵ��Ľ��" << endl;
    printVector(v1);
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
    cout << "������������Ϊ��" << v1.capacity() << endl;        // out:0
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


// vector �����ɾ��
/*- `push_back(ele);`		// β������Ԫ��ele
- `pop_back();`			// β��ɾ��һ��Ԫ��
- `insert(const_iterator pos, ele);`		// ������ָ��λ��pos����Ԫ��ele
- `insert(const_iterator pos, int count, ele);`		// ������ָ��λ��pos����count��Ԫ��ele
- `erase(const_iterator pos);`		// ɾ��������ָ���Ԫ��
- `erase(const_iterator start, const_iterator end);`		// ɾ����������start��end֮���Ԫ��
- `clear();`			// ɾ������������Ԫ��*/
void vector_011()
{
    vector<int> v1;
    init_Dim1andCout(v1);

    for (int i = 0; i < 5; i++)
    {
        v1.pop_back();      // pop_back()������������
    }
    cout << "����pop_back()ɾ��5��" << endl;
    printVector(v1);

    // �������ķ�ʽ����
    v1.insert(v1.begin() + 2, 99);
    cout << "���м��������" << endl;
    printVector(v1);

    // �������ķ�ʽɾ��
    v1.erase(v1.begin() + 2);
    cout << "ɾ��֮ǰ�����99" << endl;
    printVector(v1);

    // clear() ���
    v1.clear();
    cout << "clear()���" << endl;
    printVector(v1);
}


// vector���ݴ�ȡ
/*- `at(int idx);`		// ��������idx��ָ������
- `operator[];`			// ��������idx��ָ������
- `front();`			// ���������е�һ������Ԫ��
- `back();`				// �������������һ������Ԫ��*/
void vector_012()
{
    vector<int> v1;
    init_Dim1andCout(v1);

    cout << "����forѭ���ֱ�ȡ���������" << endl;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1.at(i) << " ";
    }
    cout << endl;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;

    cout << "��һ��Ԫ�أ�" << v1.front() << endl;;
    cout << "��һ��Ԫ�أ�" << v1.back() << endl;
}


// vector ��������
/*`swap(vec);`		// ��vec�뱾���Ԫ�ػ���*/
void vector_013()
{
    vector<int> v1;
    init_Dim1andCout(v1);

    vector<int> v2(10,0);       // ��ǰ����ÿռ�
    for (int i = 0,j = v2.size()-1; i < v2.size(); i++,j--)
    {
        v2[i] = j;
    }
    cout << "v2����������Ϊ��" << endl;
    printVector(v2);

    v2.swap(v1);
    cout << "swap()������" << endl;
    cout << "v1������Ϊ��" << endl;
    printVector(v1);
    cout << "v2������Ϊ��" << endl;
    printVector(v2);

    // Ӧ�ó���
    //      ���Բ鿴��ǰv2������
    cout << "��ǰv2������Ϊ��" << v2.capacity() << endl;
    cout << "��ǰv2��Ԫ��Ϊ��" << v2.size() << endl;
    //      ���� �������󿽱����� + swap ������С�ڴ�ռ���'����=����'
    vector<int>(v2).swap(v2);
    cout << "swap()��v2������Ϊ��" << v2.capacity() << endl;
    cout << "swap()��v2��Ԫ��Ϊ��" << v2.size() << endl;
    printVector(v2);
}


// vector Ԥ���ռ�
/*`reserve(int len);`		// ����Ԥ��len��Ԫ�س��ȣ�Ԥ��λ�ò���ʼ����Ԫ�ز��ɷ��ʡ�*/
void vector_014()
{
    vector<int> v;
    // �鿴ѹ��ʮ�������ʱ���ڴ濪�ٵĴ���
    int num = 0;
    int* p = NULL;
    for (int i = 0; i < 100000; i++)
    {
        v.push_back(i);
        if (p != &v[0])
        {
            p = &v[0];
            num++;
        }
    }
    cout << "�����ڴ�Ĵ�����" << num << endl;

    vector<int> v1;
    v1.reserve(100000);
    num = 0;
    p = NULL;
    for (int i = 0; i < 100000; i++)
    {
        v1.push_back(i);
        if (p != &v1[0])
        {
            p = &v1[0];
            num++;
        }
    }
    cout << "�����ڴ�Ĵ�����" << num << endl;
}



// vector����������
void vector_016()
{
    // �����������ǿ�����ʽ�ذ������Ԫ�س�ʼ��Ϊһ�鳣��ֵ
    int ia_a[10] = { 0,1,2,3,4,5,6,7,8,9 };
    //      ����vector���ܹ�����
    //      ����������ָ�����ʽ���������鴴������
    // ���� ia_a ����һ��ָ�룬ָ���������׵�ַ����˿�����������vector
    vector<int> ivt_v1(ia_a, ia_a+ sizeof(ia_a) / sizeof(ia_a[0]));
    printVector(ivt_v1);

    // ������;�����ж���д��
    vector<int> ivt_v2(&ia_a[3], &ia_a[9]);
    //vector<int> ivt_v2(&ia_a[3], &ia_a[8] + 1);
    //vector<int> ivt_v2(&ia_a[3], &ia_a[8+1]);
    printVector(ivt_v2);

    //vector<int> ivt_v2();   // TODO������һ����ֵĶ���

    // ��չinsert()
    //  insert(const_iterator pos, beg(), end())
    //  ͨ����˵�ǿ��Բ���ָ�뷶Χ�ڵ�����
    cout << endl;
    cout << "��v2����v1��ǰ�棺" << endl;
    ivt_v1.insert(ivt_v1.begin(), ivt_v2.begin(), ivt_v2.end());
    printVector(ivt_v1);

    cout << endl;
    cout << "���������v2���ǿ��Եģ�" << endl;
    ivt_v2.insert(ivt_v2.begin(), ia_a, ia_a + 3);
    printVector(ivt_v2);
}


// vector �����Դ�������
void vector_C11_eg001()
{
    // ֱ�������鴴������
    //  һά����
    vector<int> ivt_v1{ 1,2,3,4,5 };
    cout << "�����Դ���һά����v1��" << endl;
    printVector(ivt_v1);
    cout << endl;
    //  ��ά����
    vector<vector<int>> ivt_vv1{ {1,2,3},{2,3,4},{3,4,5} };
    printVector(ivt_vv1);
}


//�о�һ�¶�ά����
void vector_015()
{
    vector<vector<int>> v;
    cout << "�յĶ�ά�����������Ϊ��" << v.capacity() << endl;
    // ����С����
    vector<int> v1;
    cout << "�յ�һά�����������Ϊ��" << v1.capacity() << endl;
    v1 = { 1,2,3,4 };   // ��С�������������
    for (int i = 0; i < 4; i++)
    {
        v.push_back(v1);
    }
    // ͨ����������������������
    printVector(v);

    //cout << v[1][1] << endl;    // ˵������v[][]����ĳһ��Ԫ��
    //printVector(v[1]);  // ˵��v[row]��һ��vector<>�������ڵĶ���
}

//  ��ά���������
void vector_2dim001()
{
    //����һά�����ķ�ʽ��
    //  `vector(n, elem);`
    vector<int> dim1_v1(10);
    cout << "�������elem�����ʼ��Ϊ0" << endl;
    printVector(dim1_v1);
    vector<int> dim1_v2(10, 1);
    cout << "�����elem�����ʼ��Ϊelem" << endl;
    printVector(dim1_v2);
    //  ��ʵ(n,elem)�У�
    //      n��ָ��vector<>��<>�ڵ�����
    //      elem��ָ��vector<>��<>�ڵ�����

    //��һά����Ĺ�����ȵ���ά����Ĺ�����
    //  ����m*n������
    //vector<vector<int>> dim2_v1(m, vector<int>(n));
    vector<vector<int>> dim2_v1(3, vector<int>(3));
    cout << "�鿴����Ķ�ά����" << endl;
    printVector(dim2_v1);
    vector<vector<int>> dim2_v2(3, vector<int>(3, 6));
    cout << "�鿴����Ķ�ά����" << endl;
    printVector(dim2_v2);
    
    //�Զ�ά����ĵ��н��и�ֵ
    //  tips:���Գ���ԭ�����鳤�Ƚ��и�ֵ
    dim2_v2[0] = { 1,2,3,4,5,6 };
    cout << "���и�ֵ�Ķ�ά����" << endl;
    printVector(dim2_v2);

    //������ά����ֻ����һ������
    vector<vector<int>> dim2_v3(3);
    cout << "������ά����ֻ����һ������" << endl;
    printVector(dim2_v3);   //���Ϊ��
    cout << "�Ƿ��ܵ��ÿռ�" << endl;
    //dim2_v3[0][0] = 1;    //���ܵ��ÿռ䣬�м��мǣ�
}

//vector����
void vector_017()
{
    vector<int> v{ 0,1,2,3,4,5,6 };
    //����һ��v1��size()С��v.size()
    vector<int> v1(3);
    copy(v.begin(),v.begin() + 2, v1.begin());
    printVector(v1);    
    //  �ڷ�Χ�ڽ��п�����Ȼ��û������
    //copy(v.begin(), v.end(), v1.begin());
    //printVector(v1);
    ////  �ڷ�Χ����п����ͻᱨ���������

    //assign�Ƚϱ��
    //printVector((v.begin(), v.end()));
}

//��ά����resize()
void vector_2dim002()
{
    vector<vector<int>> v1(3, { 6,6,6,6,6,6 });
    cout << "��ӡ��ʼ�����Ķ�ά����" << endl;
    printVector(v1);
    cout << "��ʱ��������" << v1.capacity() << endl;  //��ֻ��һ��
    cout << "��ʱ�Ŀռ䣺" << v1.size() << endl;
    cout << "�ٴμ���������ά����" << endl;
    cout << "��ʱ��������" << v1.capacity()*v1[0].capacity() << endl;
    cout << "��ʱ�Ŀռ䣺" << v1.size()*v1[0].size() << endl;

    v1.resize(4, {0,0});    //resize����ֻ���v1<>����Ķ�������resize
    printVector(v1);
    cout << "�ٴμ���������ά����" << endl;
    cout << "��ʱ��������" << v1.capacity() * v1[0].capacity() << endl;
    cout << "��ʱ�Ŀռ䣺" << v1.size() * v1[0].size() << endl;

    v1[0].resize(12);
    printVector(v1);
    cout << "�ٴμ���������ά����" << endl;
    cout << "��ʱ��������" << v1.capacity() * v1[0].capacity() << endl;
    cout << "��ʱ�Ŀռ䣺" << v1.size() * v1[0].size() << endl;
    cout << "��Ȼ�˷����ܹ������ȷ�������͸�����" << endl;
    int cap = 0, num = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        cap += v1[i].capacity();
        num += v1[i].size();
    }
    cout << "�ٴμ���������ά����" << endl;
    cout << "��ʱ��������" << cap << endl;
    cout << "��ʱ�Ŀռ䣺" << num << endl;
}