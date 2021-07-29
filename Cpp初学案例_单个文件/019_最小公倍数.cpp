/*
encoding: GB2312(936)
*/

#include <iostream>
using namespace std;

void findCommonMultiple()
{
    int n1, n2, hcf, temp, lcm;

    cout << "����������: ";
    cin >> n1 >> n2;

    hcf = n1;
    temp = n2;

    // �������������������
    while (hcf != temp)
    {
        if (hcf > temp)
            hcf -= temp;
        else
            temp -= hcf;
    }

    // ��С������ = (�������) / �������
    lcm = (n1 * n2) / hcf;

    cout << "LCM = " << lcm;
}


// ���Ƽ�
void findCommonMultiple_N()
{
    int n1, n2, max;

    cout << "����������: ";
    cin >> n1 >> n2;

    // ��ȡ������
    max = (n1 > n2) ? n1 : n2;

    do
    {
        if (max % n1 == 0 && max % n2 == 0)
        {
            cout << "LCM = " << max;
            break;
        }
        else
            ++max;
    } while (true);
}

int main()
{
    findCommonMultiple();
    cout << endl;

    system("pause");
    return 0;
}