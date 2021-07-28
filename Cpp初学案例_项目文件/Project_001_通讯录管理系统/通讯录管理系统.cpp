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

// ���ú���
int isNull(struct AddressBooks* abs)
{
	if (abs->m_Size < 1)
	{	
		cout << "��ǰͨѶ¼Ϊ��" << endl;
		return 0;
	}
	return 1;
}

// ��ӡ��ϵ��
void prtSinglePerson(Person abs[], int i)
{
	cout << "������" << abs[i].m_Name << endl;
	cout << "�Ա�" <<
		(abs[i].m_Sex == 1 ? "��" : "Ů") << "\t";
	cout << "���䣺" << abs[i].m_Age << "\t";
	cout << "�绰" << abs[i].m_Phone << endl;
	cout << "��ַ" << abs[i].m_Addr << endl;
	cout << endl;
}

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
	if (! isNull(abs))
	{
	}
	else
	{
		cout << endl;
		for (int i = 0; i < abs->m_Size; i++)
		{
			prtSinglePerson(abs->personArray, i);
		}
	}

	// clear
	SleepAndClear();
}

// 3��ɾ����ϵ��
int isExist(AddressBooks* abs, string name)
{
	 //�ж���ϵ���Ƿ���ڣ�������ϵ�����������еľ���λ�ã������ڷŻ�-1
	for (int i = 0; i < abs->m_Size; i++)
	{
	if (abs->personArray[i].m_Name == name)
			return i;
	}
	return -1;
}

void deletePerson(AddressBooks* abs)
{	
	if (! isNull(abs))
	{
		// clear
		SleepAndClear();
		return;
	}
	cout << "����������Ҫɾ������ϵ��" << endl;
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
		// ��ѯ���������������ʵ��ɾ������
		for (int i = ret; i < abs->m_Size; i++)
		{
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size --;
		cout << "ɾ���ɹ�" << endl;
	}
	// clear
	SleepAndClear();
}

// 4��������ϵ��
void findPerson(struct AddressBooks* abs)
{
	// ���ж��Ƿ�Ϊ��
	if (!isNull(abs))
	{
		SleepAndClear();
		return;
	}
	else
	{
		cout << "������������ҵ���ϵ��������" << endl;
		string name;
		cin >> name;
		// for ѭ������
		int ret = isExist(abs, name);
		if (ret != -1)
		{
			cout << endl;
			prtSinglePerson(abs->personArray, ret);
		}
		else
		{
			cout << "��ϵ��\"" << name << "\"����ͨѶ¼��" << endl;
		}

		// cls
		SleepAndClear();
	}
}

// 5���޸���ϵ��
void modifyPerson(AddressBooks* abs)
{	
	// ���ж��Ƿ�Ϊ��
	if (!isNull(abs))
	{
		SleepAndClear();
		return;
	}
	// ��Ѱ�������ж��Ƿ����
	cout << "��������Ҫ�޸ĵ���ϵ��" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);
	if (ret == -1)
	{
		cout << "���޴���" << endl;
		system("cls");
	}
	// modify person
	else
	{
		system("cls");
		// �����˵�����
		string menuArr[] = {
			"1���޸���ϵ������",
			"2���޸���ϵ���Ա�",
			"3���޸���ϵ������",
			"4���޸���ϵ�˵绰",
			"5���޸���ϵ�˵�ַ",
			"0���˳��޸�",
		};
		while (true)
		{	
			// ��ӡ�˵�
			for (int i = 0; i < 5; i++)
			{
				cout << "****  " << menuArr[i] << "  ****" << endl;
			}
			cout << "****  " << menuArr[5] << "        ****" << endl;
			// ��ӡ��Ҫ�޸ĵ��û���Ϣ
			cout << "��ǰ�û���ϢΪ��" << endl;
			cout << endl;
			prtSinglePerson(abs->personArray,ret);

			// �û�����
			cout << "�������޸���Ŀ��" << endl;
			int mSelect;
			cin >> mSelect;
			TypeInt(&mSelect);
			string tempS;
			int tempI;
			switch (mSelect)
			{
			case 1:
				cout << "�������޸ĺ�����" << endl;
				cin >> tempS;
				abs->personArray[ret].m_Name = tempS;
				break;
			case 2:
				cout << "�������޸ĺ��Ա�" << endl;
				while (true)	// ָ������ 1 or 2
				{
					cin >> tempI;
					TypeInt(&tempI);
					if (tempI == 1 || tempI == 2)
					{
						abs->personArray[ret].m_Sex = tempI;
						break;
					}
					cout << "�Ա������������������룺";
				}
				break;
			case 3:
				cout << "�������޸ĺ�����" << endl;
				while (true)
				{
					cin >> tempI;
					TypeInt(&tempI);
					if (tempI >= 0)
					{
						abs->personArray[ret].m_Age = tempI;
						break;
					}
					else
					{
						cout << "��������ȷ���䣺" << endl;
					}
				}
				break;
			case 4:
				cout << "�������޸ĺ�绰" << endl;
				cin >> tempS;
				abs->personArray[ret].m_Phone = tempS;
				break;
			case 5:
				cout << "�������޸ĺ��ַ" << endl;
				cin >> tempS;
				abs->personArray[ret].m_Addr = tempS;
				break;
			case 0:
				system("cls");
				return;
			default:
				break;
			}
			system("cls");
		}
	}
}

// 6.�����ϵ��
void cleanPerson(AddressBooks* abs)
{
	cout << "��ǰͨѶ¼���У�" << abs->m_Size << "��" << endl;
	cout << "��ȷ���Ƿ������ϵ��(yes/no)" << endl;
	string choose;
	cin >> choose;
	if (choose == "yes")
	{
		abs->m_Size = 0;
		cout << "ͨѶ¼�����" << endl;
	}
	else
	{
		cout << "�������δ�ܳɹ������ϵ��" << endl;
	}
	SleepAndClear();
}

int main()
{
	// ����ͨѶ¼�ṹ�����
	struct AddressBooks abs;
	// ��ʼ��ͨѶ¼�еĵ�ǰ��Ա����
	abs.m_Size = 0;


	while (true)
	{
		showMenu();
		int select = 0;
		cin >> select;
		TypeInt(&select);

		switch (select)
		{
		case 1:     // "1�������ϵ��",
			addPerson(&abs);    // ���õ�ַ���ݿ�������ʵ��
			break;
		case 2:     // "2����ʾ��ϵ��",
			showPerson(&abs);
			break;
		case 3:     // "3��ɾ����ϵ��",
			deletePerson(&abs);
			break;
		case 4:     // "4��������ϵ��",
			findPerson(&abs);
			break;
		case 5:     // "5���޸���ϵ��",
			modifyPerson(&abs);
			break;
		case 6:     // "6�������ϵ��",
			cleanPerson(&abs);
			break;
		case 0:     // "0���˳�ͨѶ¼",
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
		default:
			system("cls");
			break;
		}
	}

	return 0;
}
