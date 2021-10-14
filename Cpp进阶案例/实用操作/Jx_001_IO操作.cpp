#include <fstream>
#include "../Jx_���װ���.h"

//
////�򵥻�ȡ����
//template<typename T>
//vector<T> JxTool_GetData(string filePath)
//{
//    vector<T> Array;
//    T temp;
//    std::ifstream infile(filePath);
//    if (!infile)
//    {
//        std::cout << "Unable to read file." << std::endl;
//        return Array;
//    }
//    while (!infile.eof())            // ��δ���ļ�����һֱѭ��
//    {
//        infile >> temp;
//        Array.push_back(temp);
//    }
//    return Array;
//}

/*-- ���׶�д�̳� --*/
void Jx_IOStream_001()
{
	//1.����ͷ�ļ� fstream
	//2.����������
	ofstream ofs;
	//3.ָ���򿪷�ʽ
	ofs.open("test.txt", ios::out);		//ûдȨ�޺���Ҳ������ɶ����
	//4.д����
	ofs << "����������" << endl;
	ofs << "����������" << endl;
	ofs << "����������" << endl;
	//5.�ر��ļ�
	ofs.close();
}
void Jx_IOStream_002()
{
	//1.����ͷ�ļ� fstream
	//2.����������
	ifstream ifs;
	//3.���ļ� �����ж��Ƿ�򿪳ɹ�
	ifs.open("test.txt", ios::in);

	if (!ifs.is_open()) { cout << "�ļ���ʧ��" << endl; return; }
	//4.������
	/*��һ��*/
	//char buf[1024] = { 0 };
	//while (ifs >> buf)
	//{
	//	cout << buf << endl;
	//}
	/*�ڶ���*/
	/*char buf[1024] = { 0 };
	while (ifs.getline(buf,sizeof(buf)))
	{
		cout << buf << endl;
	}*/
	/*������*/
	/*string buf;
	while (getline(ifs,buf))
	{
		cout << buf << endl;
	}*/
	/*������*/
	//���Ƽ�
	char c;
	while ( (c = ifs.get()) != EOF )	// EOF
	{
		cout << c;
	}
	//5.�ر��ļ�
	ifs.close();
}
//�������ļ� д�ļ�
class Person
{
public:
	char m_Name[64];	//����
	int m_Age;			//����
};
void Jx_IOStream_003()
{
	ofstream ofs;
	ofs.open("Person.txt", ios::out | ios::binary);
	Person p = { "����",18 };
	ofs.write( (const char *)&p, sizeof(p));
	ofs.close();
}
//�������ļ� ���ļ�
void Jx_IOStream_004()
{
	ifstream ifs;
	ifs.open("Person.txt", ios::in | ios::binary);
	if (!ifs.is_open()) { cout << "�ļ���ʧ��" << endl; return; }
	Person p;
	ifs.read((char*)&p, sizeof(p));
	ifs.close();
	cout << p.m_Name << endl;
	cout << p.m_Age << endl;
}
