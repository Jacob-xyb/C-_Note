#include <fstream>
#include <sstream> 
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

/*-- ���׶�ȡtxt�ļ� --*/
void read_txt_001(std::string& path, std::vector<double>& data)
{
	std::ifstream ifs;
	ifs.open(path, std::ios::in);
	double temp;
	while (ifs >> temp)
	{
		data.push_back(temp);
	}
	ifs.close();
}

void call_read_txt_001()
{
	std::string path = "D:\\1.company\\GitLab\\DA_Test\\Test-DA-Jx-Proj\\nk.txt";
	std::vector<double> data;
	read_txt_001(path, data);
	for (size_t i = 0; i < data.size(); i+=3)
	{
		std::cout << data[i] << "\t" << data[i + 1] << "\t" << data[i + 2] << std::endl;
	}
}

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
	/*string line;
	while (getline(ifs,line))
	{
		cout << line << endl;
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

void Jx_read_csv(string fileName)
{
	vector<double> data;

	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open()) { cout << "�ļ���ʧ��" << endl; return; }
	string line;
	int num = 0;
	while (getline(ifs, line))
	{
		istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
		string field;
		if (num == 0)
		{
			++num;
			continue;
		}
		while (getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
		{
			double temp;
			temp = stod(field);
			data.push_back(temp); //���ոն�ȡ���ַ�����ӵ�����fields��
		}
		++num;
	}
	ifs.close();

	cout << data.size() << endl;
}

template<typename T_>
void Jx_ReadTxt(std::string& path, std::vector<T_>& data)
{
	std::ifstream ifs;
	ifs.open(path, std::ios::in);
	if (!ifs.is_open()) { std::cout << "�ļ���ʧ��" << std::endl; return; }
	T_ temp;
	while (ifs >> temp)
	{
		data.push_back(temp);
	}
	ifs.close();
}