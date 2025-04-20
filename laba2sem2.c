#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Функция, которая находит самую длинную последовательность повторяющихся символов из файла
void find_longest_repeating_sequence_in_file(const char* filename, char* result, int* length) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Ошибка открытия файла для чтения.\n");
        return;
    }

    int ch, prev;
    int current_length = 0;
    int max_length = 0;
    char max_char = '\0';

    // Считываем первый символ, если файл не пустой
    prev = fgetc(fp);
    if (prev == EOF) {
        printf("Файл пустой.\n");
        fclose(fp);
        return;
    }
    current_length = 1;

    // Считываем остальной файл по символам
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == prev) {
            // Повторяющийся символ, увеличиваем счётчик
            current_length++;
        }
        else {
            // Проверка текущей последовательности
            if (current_length > max_length) {
                max_length = current_length;
                max_char = prev;
            }
            // Сброс счетчика и запоминаем текущий символ
            current_length = 1;
            prev = ch;
        }
    }
    // Проверка последней последовательности
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

// Функция, которая заменяет слова заданной длины на пробелы
void replace_words_with_spaces(const char* filename, int count) {
    FILE* fp = fopen(filename, "r+");
    if (!fp) {
        printf("Ошибка открытия файла для чтения.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char* content = (char*)malloc(size + 1);
    if (content == NULL) {
        printf("Ошибка выделения памяти.\n");
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

    // Проверка последнего слова в файле
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

    // Проверка на количество аргументов: имя файла
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];

    FILE* file;
    // 1. Заполнение файла словами с клавиатуры
    printf("Введите слова (для завершения введите 'end'):\n");
    file = fopen(filename, "wt");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи.\n");
        return 1;
    }

    int ch;
    char last_chars[4] = { 0 }; // Массив для хранения последних 3 символов
    int index = 0;
    while (1) {
        ch = getchar();
        if (ch == EOF) break;

        // Проверка на слово 'end'
        last_chars[index] = ch;
        if (last_chars[index] == 'd' && last_chars[(index + 2) % 3] == 'n' && last_chars[(index + 1) % 3] == 'e') {
            break;
        }

        // Запись символа в файл
        fputc(ch, file);
        index = (index + 1) % 3;
    }
    fclose(file);

    // Чтение содержимого файла без последних двух символов и вывод на экран
    printf("\nСодержимое файла %s:\n", filename);
    file = fopen(filename, "rt");
    if (file == NULL) {
        printf("Ошибка открытия файла для чтения.\n");
        return 1;
    }

    long size;
    fseek(file, 0, SEEK_END);
    size = ftell(file); // Получение размера файла
    rewind(file);       // Возврат указателя файла в начало

    for (long i = 0; i < size - 2; i++) {
        ch = fgetc(file);
        if (ch == EOF) break;
        putchar(ch);
    }
    fclose(file);

    // Поиск самой длинной последовательности повторяющихся символов из файла
    char result[100];
    int length = 0;
    find_longest_repeating_sequence_in_file(filename, result, &length);

    printf("\n\nСамая длинная последовательность повторяющихся символов: '%s' (длина: %d)\n", result, length);

    // Запрашиваем у пользователя количество символов для замены
    printf("Введите количество символов для замены на пробелы: ");
    int check2 = 0;
    float l;
    int count;
    while (!check2) {
        check2 = scanf("%f", &l);
        while (getchar() != '\n');
        if (!check2) {
            printf("Некорректный ввод.\n");
        }
        else {
            count = (int)l;
            if (count != l) {
                printf("Введите целое число: ");
                check2 = 0;
            }
            else if (count < 0) {
                printf("Введите число больше нуля\n");
                check2 = 0;
            }
        }
    }

    // Замена указанных слов на пробелы в файле
    replace_words_with_spaces(filename, count);

    // Чтение и вывод содержимого файла после замены слов на пробелы
    printf("\nСодержимое файла %s:\n", filename);
    file = fopen(filename, "rt");
    if (file == NULL) {
        printf("Ошибка открытия файла для чтения.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file); // Получение размера файла
    rewind(file);       // Возврат указателя файла в начало

    for (long i = 0; i < size - 2; i++) {
        ch = fgetc(file);
        if (ch == EOF) break;
        putchar(ch);
    }
    fclose(file);

    return 0;
}
