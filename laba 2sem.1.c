#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>

// ������� ��� ���������� ����� ������������� � ������������ ��������
int sum_max_min(const char* filename, int count) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("������ ��� �������� �����");
        return 1;
    }

    int min = INT_MAX;
    int max = INT_MIN;
    int num;

    // ������� ����������� � ������������ ��������
    for (int i = 0; i < count; i++) {
        fread(&num, sizeof(int), 1, file);
        if (num < min) {
            min = num;
        }
        if (num > max) {
            max = num;
        }
    }

    fclose(file);

    // ���������� ����� ������������ � ������������� ���������
    return min + max;
}

// ������� ��� ��������� ��������� �� ���������� ��������
void zero_elements(FILE* file, int count) {
    int num;
    int pos = 0;

    while (pos < count) {
        // ������������� � ������� �������
        fseek(file, pos * sizeof(int), SEEK_SET);

        // ��������� �������� � ������� �������
        fread(&num, sizeof(int), 1, file);

        // ���� �������� �������, �������� ����
        if (num == 0) {
            break;
        }

        // �������� �������� � ������� �������
        fseek(file, pos * sizeof(int), SEEK_SET);
        int zero = 0;
        fwrite(&zero, sizeof(int), 1, file);

        // ������������� �� ��������, ��������� � ������ �� ���������
        pos += num;
    }
}

// ������� ��� �������� ���� ����� �� �����
void remove_zeros(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("������ ��� �������� �����");
        return;
    }

    FILE* temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        perror("������ ��� �������� ���������� �����");
        fclose(file);
        return;
    }

    int num;
    while (fread(&num, sizeof(int), 1, file)) {
        if (num != 0) {
            fwrite(&num, sizeof(int), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    // ���������� ������������� ����� ��� �����
    remove(filename);
    rename("temp.bin", filename);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    // �������� �� ���������� ����������
    if (argc != 2) {
        printf("�������������: %s <���_�����>\n", argv[0]);
        return 1;
    }

    // �������� ��� ��������� ����� �� ������� ���������
    const char* filename = argv[1];

    // �������� ����� ��� ������ � �������� ������
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("������ ��� �������� �����");
        return 1;
    }

    // ����������� � ������������ ���������� ����� ��� ������
    int count;
    printf("������� ���������� ����� ��� ������: ");
    scanf("%d", &count);

    // ������ ������ � �������� ����
    int num;
    for (int i = 0; i < count; i++) {
        printf("������� ����� %d: ", i + 1);
        scanf("%d", &num);
        fwrite(&num, sizeof(int), 1, file);
    }

    printf("������ ������� �������� � ���� %s\n", filename);

    // �������� ����� ����� ������
    fclose(file);

    // �������� ����� ��� ������ � ������ � �������� ������
    file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("������ ��� �������� �����");
        return 1;
    }

    // ������ ������ �� ��������� ����� � ����� �� �����
    printf("���������� ����� %s:\n", filename);
    for (int i = 0; i < count; i++) {
        fread(&num, sizeof(int), 1, file);
        printf("%d\n", num);
    }

    // ���������� � ����� ����� ������������� � ������������ ��������
    int sum = sum_max_min(filename, count);
    printf("����� ������������� � ������������ ��������: %d\n", sum);

    // ��������� ��������� �� ���������� ��������
    zero_elements(file, count);

    // ������ ���������� ������ �� ����� � ����� �� �����
    fseek(file, 0, SEEK_SET);
    printf("\n���� ����� ��������� ���������:\n");
    for (int i = 0; i < count; i++) {
        fread(&num, sizeof(int), 1, file);
        printf("%d ", num);
    }
    printf("\n");

    // �������� ����� ����� ���������
    fclose(file);

    // �������� ���� ����� �� �����
    remove_zeros(filename);

    // �������� ����� ��� ������ ����� �������� �����
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("������ ��� �������� �����");
        return 1;
    }

    // ������ ������ �� ����� ��� ����� � ����� �� �����
    printf("\n���� ����� �������� �����:\n");
    while (fread(&num, sizeof(int), 1, file)) {
        printf("%d ", num);
    }
    printf("\n");

    // �������� ����� ����� �������� �����
    fclose(file);

    return 0;
}
