// GB2312(936)
#include <iostream>
#include "..\function.h"
using namespace std;

// global const
#define MAX 1000		// �������
// ��ʾ�˵�����

// ��ϵ㣬����


void showMenu()
{
	// ��������
	string menuArr[] = {
		"1�������ϵ��",
		"2����ʾ��ϵ��",
		"3��ɾ����ϵ��",
		"4��������ϵ��",
		"5���޸���ϵ��",
		"6�������ϵ��",
		"0���˳�ͨѶ¼",
	};

	// main
	printStart(5 * 2 + 2 * 2 + 1 + 2 * 6);
	cout << endl;
	for (int i = 0; i < 7; i++)
	{
		printStart(5);
		cout << "  " << menuArr[i] << "  ";
		printStart(5);
		cout << endl;
	}
	printStart(5 * 2 + 2 * 2 + 1 + 2 * 6);
	cout << endl;
}

 //�ṹ�壺��
struct Person
{
	// �������Ա����䣻�绰����ַ
	string m_Name;
	int m_Sex;      // �Ա� 1�� 2Ů
	int m_Age;
	string m_Phone;
	string m_Addr;
};


struct AddressBooks
{
	struct Person personArray[MAX];
	int m_Size;     // ͨѶ¼����Ա����
};

// 1�������ϵ��
void addPerson(struct AddressBooks* abs)
{
	// �ж�ͨѶ¼�Ƿ�������������˾Ͳ������
	if (abs->m_Size == MAX)
	{
		cout << "ͨѶ¼�������޷���ӣ�" << endl;
		return;
	}
	else
	{
		// ��Ӿ�����ϵ��
		// add ����
		cout << "������������" << endl;
		string name;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;
		// add �Ա�
		cout << "�������Ա�" << endl;
		cout << "1 --- ��" << endl;
		cout << "2 --- Ů" << endl;
		int sex;
		while (true)
		{
			cin >> sex;
			TypeInt(&sex);
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "�Ա������������������룺";
		}
		// add age
		int age;
		cout << "���������䣺" << endl;
		while (true)
		{
			cin >> age;
			TypeInt(&age);
			if (age >= 0)
			{
				abs->personArray[abs->m_Size].m_Age = age;
				break;
			}
			else
			{
				cout << "��������ȷ���䣺" << endl;
			}
		}

		// add phone
		string phone;
		cout << "������绰���룺" << endl;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		// add address
		cout << "������סַ��" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		// update adressBook
		abs->m_Size++;
		cout << "��ӳɹ�" << endl;

		// clear
		SleepAndClear();
	}
}

// 2����ʾ��ϵ��
void showPerson(struct AddressBooks* abs)
{
	// ���ж�ͨѶ¼����
	if (abs->m_Size == 0)
	{
		cout << "��ǰ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "������" << abs->personArray[i].m_Name << endl;
			cout << "�Ա�" <<
				(abs->personArray[i].m_Age == 1 ? "��" : "Ů") << "\t";
			cout << "���䣺" << abs->personArray[i].m_Age << "\t";
			cout << "�绰" << abs->personArray[i].m_Phone << endl;
			cout << "��ַ" << abs->personArray[i].m_Addr << endl;
		}
	}

	// clear
	SleepAndClear();
}

// 3��ɾ����ϵ��
// �ж���ϵ���Ƿ���ڣ�������ϵ�����������еľ���λ�ã������ڷŻ�-1
int isExist(AddressBooks* abs, string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		if (abs->personArray[i].m_Name == name)
			return i;
	}
	return -1;
}

void deletePerson(AddressBooks* abs)
{
	cout << "��������Ҫ����ϵ��" << endl;
	string name;
	cin >> name;
	// ret == -1 û�鵽
	int ret = isExist(abs, name);
	if (ret == -1)
	{
		cout << "���޴���" << endl;
	}
	else
	{
		// TODO
	}
}

int main()
{
	// ����ͨѶ¼�ṹ�����
	struct AddressBooks abs;
	// ��ʼ��ͨѶ¼�еĵ�ǰ��Ա����
	abs.m_Size = 0;
	int select = 0;

	while (true)
	{
		showMenu();

		cin >> select;

		switch (select)
		{
		case 1:     // "1�������ϵ��",
			addPerson(&abs);    // ���õ�ַ���ݿ�������ʵ��
			break;
		case 2:     // "2����ʾ��ϵ��",
			showPerson(&abs);
			break;
		case 3:     // "3��ɾ����ϵ��",
			break;
		case 4:     // "4��������ϵ��",
			break;
		case 5:     // "5���޸���ϵ��",
			break;
		case 6:     // "6�������ϵ��",
			break;
		case 0:     // "0���˳�ͨѶ¼",
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}

		cout << endl;
	}

	return 0;
}
