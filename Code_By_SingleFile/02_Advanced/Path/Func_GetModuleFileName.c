#include <stdio.h>
#include <Windows.h>

int main(int argc, char const *argv[])
{
    char cFilePath[MAX_PATH];		// �ļ�·��
    memset(cFilePath, 0, MAX_PATH);
    int size = GetModuleFileName(NULL, (LPSTR)cFilePath, MAX_PATH);

    printf("path=%s\nsize=%d\n", cFilePath, size);
    // ע�⣺��ȡ���� .exe �ļ�������·��

    return 0;
}
