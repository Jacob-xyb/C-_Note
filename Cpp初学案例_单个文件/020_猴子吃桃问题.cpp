/*
encoding: GB2312(936)
state:һֻС����һ��ժ��������ӣ���һ�����һ�룬Ȼ���̲�ס�ֳ���һ�����ڶ����ֳ���һ�룬�ټ���һ����
        ����ÿ�춼�������ԡ�����10���ʱ��С���ӷ���ֻ��һ�������ˡ�
        ��С���ӵ�һ�칲ժ�˶��ٸ����ӡ�
*/

#include <iostream>
using namespace std;

int main()
{
    int x = 1;
    for (int i = 0; i < 10-1; i++)
    {
        x = (x + 1) * 2;
        
    }
    //int x, y, n;
    //for (x = 1, n = 0; n < 9; y = (x + 1) * 2, x = y, n++);

    cout << "��һ�칲ժ����������Ϊ " << x << endl;

    system("pause");
    return 0;
}