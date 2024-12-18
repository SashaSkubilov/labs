#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
int fillingstr() {





 }
void removeExtraSpaces(char* str) {
    int i = 0, j = 0;
    int inSpaces = 0; // ���� ��� ������������ ��������

    while (str[i]) {
        // ���� ������� ������ �� ������
        if (str[i] != ' ') {
            str[j++] = str[i];
            inSpaces = 0; // ���������� ���� ��������
        }
        else if (inSpaces == 0) {
            // ���� ��� ������ ������ ����� �����
            str[j++] = ' ';
            inSpaces = 1; // ������������� ���� ��������
        }
        i++;
    }

    // ������� ��������� ������, ���� �� ����
    if (j > 0 && str[j - 1] == ' ') {
        j--;
    }

    str[j] = '\0'; // ��������� ������
}

int main() {
    setlocale(LC_ALL, "rus");
    char* str = (char*)malloc(100 * sizeof(char)); // ������������ ��������� ������

    if (str == NULL) {
        printf("������ ��������� ������\n");
        return 1;
    }

    printf("������� ������: ");
    fgets(str, 100, stdin);

    removeExtraSpaces(str);

    printf("������ ��� ������ ��������: '%s'\n", str);

    free(str); // ������������ ���������� ������
    return 0;
}