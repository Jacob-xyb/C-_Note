#include <stdio.h>

/// @brief -: ��%�����-��ʾ����룬ǰ����������Ĭ�Ͽ��
void sign_test_leftAlign();

/// @brief +:�з���ֵ��ʾ������
void sign_test_showsign();

/// @brief space: �з���ֵΪ����ǰ����ʾһ���ո�Ϊ����ǰ����ʾ����
void sign_test_space();

/// @brief #:�ѽ��ת��Ϊ��һ����ʽ
void sign_test_sharp();

/// @brief 0:����ռ���ǰ��0��䣻����������ʽ���������-��ǻ�ָ�����ȣ�����Ըñ�ǡ�
void sign_test_zero();

int main(int argc, char const *argv[])
{
    sign_test_leftAlign();
    sign_test_showsign();
    sign_test_space();
    sign_test_sharp();
    sign_test_zero();
    return 0;
}

void sign_test_leftAlign()
{
    printf("++ sign_test_leftAlign ++\n");

    char content[] = "hello";
    printf("*%s*\n", content);
    printf("*%-s*\n", content);   // �ڲ����ÿ�ȵ�����£�����ޱ仯
    printf("*%10s*\n", content);  // Ĭ���Ҷ���
    printf("*%-10s*\n", content); // ���������

    printf("++ sign_test_leftAlign END ++\n\n");
}

void sign_test_showsign()
{
    printf("++ sign_test_showsign ++\n");

    // ��%s��Ч
    char content[] = "hello";
    printf("%s\n", content);
    printf("%+s\n", content);

    // ���޷���ֵ��Ч
    unsigned int u_int = 123;
    printf("%u\n", u_int);  // 123
    printf("%+u\n", u_int); // 123

    // ֻ���з���ת������Ч
    printf("%+d\n", u_int); // +123

    printf("++ sign_test_showsign END ++\n\n");
}

void sign_test_space()
{
    printf("++ sign_test_space ++\n");

    printf("*%d*\n", 123);
    printf("*% d*\n", 123);
    printf("*%   d*\n", 123); // ����ո��Ч��һ���ո�
    printf("*% d*\n", -123);  // Ϊ����ǰ����ʾһ������

    printf("++ sign_test_space END ++\n\n");
}

void sign_test_sharp()
{
    printf("++ sign_test_sharp ++\n");

    // ���ڽ���������������ǰ��ʾ���Ʊ�ʾ��ʽ 0,0x ��
    printf("%%o(10):%o\n", 10);   // 12
    printf("%%#o(10):%#o\n", 10); // 012

    // ���ڸ����ʽ��#��֤�˼�ʹ����û���κ����֣�Ҳ��ӡһ��С����
    printf("%%.f(10):%.f\n", 10.);   // 10
    printf("%%#.f(10):%#.f\n", 10.); // 10.

    printf("%%.g(10):%.g\n", 10.);   // 1e+001
    printf("%%#.g(10):%#.g\n", 10.); // 1.e+001

    printf("++ sign_test_sharp END ++\n\n");
}

void sign_test_zero()
{
    printf("++ sign_test_sharp ++\n");

    printf("%%05d(10):%05d\n", 10);   // 00010
    printf("%%05d(10):%05.3d\n", 10); //  010

    printf("++ sign_test_sharp END ++\n\n");
}
