#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// �������, ������� ������� ����� ������� ������������������ ������������� �������� �� �����
void find_longest_repeating_sequence_in_file(const char* filename, char* result, int* length) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("������ �������� ����� ��� ������.\n");
        return;
    }

    int ch, prev;
    int current_length = 0;
    int max_length = 0;
    char max_char = '\0';

    // ��������� ������ ������, ���� ���� �� ������
    prev = fgetc(fp);
    if (prev == EOF) {
        printf("���� ������.\n");
        fclose(fp);
        return;
    }
    current_length = 1;

    // ��������� ��������� ���� �� ��������
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == prev) {
            // ������������� ������, ����������� �������
            current_length++;
        }
        else {
            // �������� ������� ������������������
            if (current_length > max_length) {
                max_length = current_length;
                max_char = prev;
            }
            // ����� �������� � ���������� ������� ������
            current_length = 1;
            prev = ch;
        }
    }
    // �������� ��������� ������������������
    if (current_length > max_length) {
        max_length = current_length;
        max_char = prev;
    }

    *length = max_length;
    for (int i = 0; i < max_length; i++) {
        result[i] = max_char;
    }
    result[max_length] = '\0';
    fclose(fp);
}

// �������, ������� �������� ����� �������� ����� �� �������
void replace_words_with_spaces(const char* filename, int count) {
    FILE* fp = fopen(filename, "r+");
    if (!fp) {
        printf("������ �������� ����� ��� ������.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char* content = (char*)malloc(size + 1);
    if (content == NULL) {
        printf("������ ��������� ������.\n");
        fclose(fp);
        return;
    }

    fread(content, 1, size, fp);
    content[size] = '\0';
    rewind(fp);

    char* start = content;
    char* end = content;
    int word_length = 0;

    while (*end != '\0') {
        if (*end == ' ' || *end == '\n' ) {
            if (word_length == count) {
                for (char* ptr = start; ptr < start + word_length; ptr++) {
                    *ptr = ' ';
                }
            }
            word_length = 0;
            end++;
            start = end;
        }
        else {
            word_length++;
            end++;
        }
    }

    // �������� ���������� ����� � �����
    if (word_length == count) {
        for (char* ptr = start; ptr < start + word_length; ptr++) {
            *ptr = ' ';
        }
    }

    fwrite(content, 1, size, fp);
    fclose(fp);
    free(content);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    // �������� �� ���������� ����������: ��� �����
    if (argc != 2) {
        printf("�������������: %s <���_�����>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];

    FILE* file;
    // 1. ���������� ����� ������� � ����������
    printf("������� ����� (��� ���������� ������� 'end'):\n");
    file = fopen(filename, "wt");
    if (file == NULL) {
        printf("������ �������� ����� ��� ������.\n");
        return 1;
    }

    int ch;
    char last_chars[4] = { 0 }; // ������ ��� �������� ��������� 3 ��������
    int index = 0;
    while (1) {
        ch = getchar();
        if (ch == EOF) break;

        // �������� �� ����� 'end'
        last_chars[index] = ch;
        if (last_chars[index] == 'd' && last_chars[(index + 2) % 3] == 'n' && last_chars[(index + 1) % 3] == 'e') {
            break;
        }

        // ������ ������� � ����
        fputc(ch, file);
        index = (index + 1) % 3;
    }
    fclose(file);

    // ������ ����������� ����� ��� ��������� ���� �������� � ����� �� �����
    printf("\n���������� ����� %s:\n", filename);
    file = fopen(filename, "rt");
    if (file == NULL) {
        printf("������ �������� ����� ��� ������.\n");
        return 1;
    }

    long size;
    fseek(file, 0, SEEK_END);
    size = ftell(file); // ��������� ������� �����
    rewind(file);       // ������� ��������� ����� � ������

    for (long i = 0; i < size - 2; i++) {
        ch = fgetc(file);
        if (ch == EOF) break;
        putchar(ch);
    }
    fclose(file);

    // ����� ����� ������� ������������������ ������������� �������� �� �����
    char result[100];
    int length = 0;
    find_longest_repeating_sequence_in_file(filename, result, &length);

    printf("\n\n����� ������� ������������������ ������������� ��������: '%s' (�����: %d)\n", result, length);

    // ����������� � ������������ ���������� �������� ��� ������
    printf("������� ���������� �������� ��� ������ �� �������: ");
    int check2 = 0;
    float l;
    int count;
    while (!check2) {
        check2 = scanf("%f", &l);
        while (getchar() != '\n');
        if (!check2) {
            printf("������������ ����.\n");
        }
        else {
            count = (int)l;
            if (count != l) {
                printf("������� ����� �����: ");
                check2 = 0;
            }
            else if (count < 0) {
                printf("������� ����� ������ ����\n");
                check2 = 0;
            }
        }
    }

    // ������ ��������� ���� �� ������� � �����
    replace_words_with_spaces(filename, count);

    // ������ � ����� ����������� ����� ����� ������ ���� �� �������
    printf("\n���������� ����� %s:\n", filename);
    file = fopen(filename, "rt");
    if (file == NULL) {
        printf("������ �������� ����� ��� ������.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file); // ��������� ������� �����
    rewind(file);       // ������� ��������� ����� � ������

    for (long i = 0; i < size - 2; i++) {
        ch = fgetc(file);
        if (ch == EOF) break;
        putchar(ch);
    }
    fclose(file);

    return 0;
}
