#include <stdio.h>

void ScaleNumber_BasicShow()
{
    // ������ 28 Ϊ����
    int xDec = 28;      // ʮ����
    int xHex = 0x1c;    // ʮ������ 0x
    int xOct = 034;     // �˽��� 0
    int xBin = 0b11100; // ������ 0b
    // Tips: �������е�C���Զ��ж����Ʊ�ʾ��

    printf("Dec=%d, xHex=%d, Oct=%d, Bin=%d\n", xDec, xHex, xOct, xBin);
}

int main(int argc, char const *argv[])
{
    ScaleNumber_BasicShow();
    return 0;
}
