#include <iostream>
#include <time.h>
#include "�����������.h"
using namespace std;


int main()
{
	for (int i = 0; i < 4; i++)
	{
		double step = bool(i != 0) * pow(10, -i) * 1e-2;
		cout << step << endl;
	}
    srand(time(NULL)); /*���ݵ�ǰʱ�����á���������ӡ�*/
    //test_Jx();
    system("pause");
    return 0;
}