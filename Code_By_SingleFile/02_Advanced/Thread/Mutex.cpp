// need use vs to run

#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <list>

using namespace std;

class SeaKing
{
public:
	void makeFriend()
	{
		for (int i = 0; i < 10000; i++)
		{
			// m_mutex.lock();        //����
			printf("����һ��Ů����:%d", i);
			mm.push_back(i);
			// m_mutex.unlock();      //����
		}
	}
	void breakUp()
	{
		for (int i = 0; i < 10000; i++)
		{
			if (!mm.empty())
			{
				// m_mutex.lock();        //����
				printf("����һ��Ů����:%d\n", mm.back());
				mm.pop_back();
				// m_mutex.unlock();      //����
			}
			else
			{
				printf("�����䵥��!\n");
			}
		}
	}
protected:
	list<int> mm;        //��������
	mutex m_mutex;				//���ȵ�һ������һ������������
};

int main()
{
	SeaKing man;
	thread t1(&SeaKing::makeFriend, &man);  //���������߳�
	thread t2(&SeaKing::breakUp, &man);
	t1.join();
	t2.join();
	return 0;
}