#include <iostream>

using namespace std;

void CharInitError()
{
    string str1 = "Hello World";
    // char chars1[] = str1;  // string �Ǳ������������ڳ�ʼ�� char[]
    // char chars1[] = str1.c_str();  // char* ���ܶ� char[] ��ֵ

    char charHello[] = "Hello World";
    // char chars1[] = charHello;   // char* ���ܶ� char[] ��ֵ
}

int main(int argc, char const *argv[])
{
    return 0;
}
