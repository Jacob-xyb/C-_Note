#include <iostream>
using namespace std;

int main()
{
    int year;
    string choose;
    while (true)
    {
        cout << "�������: ";
        cin >> year;

        if (year % 4 == 0)
        {
            if (year % 100 == 0)
            {
                // // ��������� 400 ����������
                if (year % 400 == 0)
                    cout << year << " ������";
                else
                {
                    cout << year << " ��������";
                }
            }
            else
            {
                cout << year << " ������";
            }
        }
        else
        {
            cout << year << " ��������";
        }

        cout << endl; 
        cout << "�Ƿ����(yes/no)" << endl;
        cin >> choose;
        if (choose == "no" || choose == "n")    
        {
            system("pause");
            return 0;
        }
        else
        {
            system("cls");
        }
    }
}