#include <iostream>
#include "workerManager.h"

using namespace std;

#include "employee.h"
#include "manager.h"
#include "boss.h"

void test()
{
	Worker* worker = NULL;
	worker = new Employee(1, "����", 1);
	worker->showInfo();
	delete worker;

	worker = new Manager(2, "����", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "����", 3);
	worker->showInfo();
	delete worker;
}

int main()
{
	WorkerManager wm;

	int choice = 0;		//�洢�û���ѡ��

	while (true)
	{
		//չʾ�˵���Ա����
		wm.Show_Menu();

		cout << "����������ѡ�� " << endl;
		cin >> choice;	//�����û���ѡ��

		switch (choice)
		{
		case 0:				//�˳��������
			wm.ExitSystem();
			break;
		case 1:				//����ְ����Ϣ
			break;
		case 2:				//��ʾְ����Ϣ
			break;
		case 3:				//ɾ����ְְ��	
			break;
		case 4:				//�޸�ְ����Ϣ
			break;
		case 5:				//����ְ����Ϣ
			break;
		case 6:				//���ձ������
			break;
		case 7:				//��������ĵ�
			break;
		default:
			system("cls");
			break;
		}
	}

	std::cout << "press [ENTER] to exit " << std::endl;
	std::cin.get();
	return 0;
}