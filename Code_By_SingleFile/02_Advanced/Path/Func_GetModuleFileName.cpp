#include <iostream>
#include <stdio.h>
#include <Windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
    char cFilePath[MAX_PATH];		// �ļ�·��
    memset(cFilePath, 0, MAX_PATH);
    int size = GetModuleFileName(NULL, (LPSTR)cFilePath, MAX_PATH);

    printf("path=%s\nsize=%d\n", cFilePath, size);
    // ע�⣺��ȡ���� .exe �ļ�������·��

    // ������ȡ·��
    string strModuleFoldPath = string(cFilePath);
    int iFind = strModuleFoldPath.rfind('\\');
    strModuleFoldPath = strModuleFoldPath.substr(0, iFind);
    printf("dir=%s\n", strModuleFoldPath.c_str());

    return 0;
}
