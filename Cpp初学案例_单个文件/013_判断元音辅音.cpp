#include<iostream> 
using namespace std;

int main() 
{

    int isLowercaseVowel, isUppercaseVowel;
    cout << "����һ����ĸ��";
    char c;
    cin >> c;
    bool ischar;
    ischar = ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    if (ischar)
    {
        // Сд��ĸԪ��
        isLowercaseVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
        // ��д��ĸԪ��
        isUppercaseVowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
        // if ����ж�
        if (isLowercaseVowel || isUppercaseVowel)
            cout << c << " ��Ԫ��";
        else
            cout << c << " �Ǹ���";
    }
    else 
    {
        cout << "����Ĳ�����ĸ��";
    }

    return 0;
}