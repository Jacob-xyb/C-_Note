/*
������������ by (for ѭ��)
˵������1~100��������ָ�λ����7������ʮλ����7��������7�ı����ʹ�ӡ�����ӣ���������ֱ�Ӵ�ӡ�����
*/

#include <iostream>
using namespace std;

int main(){

    for (int i = 1; i < 100; i++){
		if ((i % 10 == 7) or (i / 10 == 7) or (i % 7 ==0)){
			cout << "������" << endl;
		}
		else
		{
			cout << i << endl;
		}
	}

    system("pause");

    return 0;

}