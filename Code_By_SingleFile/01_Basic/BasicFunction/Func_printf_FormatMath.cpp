#include <iostream>
#include <stdio.h>

using namespace std;

void Func_s_print_string()
{
    string str1 = "hello world1";
    printf("%s\n", str1);       // �޷���ȷ���
    // string���͵Ķ��󲢷ǵ���ֻ���ַ��������ڻ���������ڲ����ĺ���
    // string.c_str() �Ż᷵���ַ������׵�ַ
    printf("%s\n", str1.c_str());

    char str2[] = "hello world2";
    printf("%s\n", str2);
}

int main(int argc, char const *argv[])
{
    return 0;
}
