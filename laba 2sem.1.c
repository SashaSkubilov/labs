#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>

// Функция для нахождения суммы максимального и минимального элемента
int sum_max_min(const char* filename, int count) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    int min = INT_MAX;
    int max = INT_MIN;
    int num;

    // Находим минимальный и максимальный элементы
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

    // Возвращаем сумму минимального и максимального элементов
    return min + max;
}

// Функция для зануления элементов по указанному принципу
void zero_elements(FILE* file, int count) {
    int num;
    int pos = 0;

    while (pos < count) {
        // Переместиться к текущей позиции
        fseek(file, pos * sizeof(int), SEEK_SET);

        // Прочитать значение в текущей позиции
        fread(&num, sizeof(int), 1, file);

        // Если значение нулевое, прервать цикл
        if (num == 0) {
            break;
        }

        // Занулить значение в текущей позиции
        fseek(file, pos * sizeof(int), SEEK_SET);
        int zero = 0;
        fwrite(&zero, sizeof(int), 1, file);

        // Переместиться на значение, указанное в ячейке до зануления
        pos += num;
    }
}

// Функция для удаления всех нулей из файла
void remove_zeros(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return;
    }

    FILE* temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        perror("Ошибка при создании временного файла");
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

    // Перезапись оригинального файла без нулей
    remove(filename);
    rename("temp.bin", filename);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    // Проверка на количество аргументов
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    // Получаем имя бинарного файла из первого аргумента
    const char* filename = argv[1];

    // Открытие файла для записи в бинарном режиме
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    // Запрашиваем у пользователя количество чисел для записи
    int count;
    printf("Введите количество чисел для записи: ");
    scanf("%d", &count);

    // Запись данных в бинарный файл
    int num;
    for (int i = 0; i < count; i++) {
        printf("Введите число %d: ", i + 1);
        scanf("%d", &num);
        fwrite(&num, sizeof(int), 1, file);
    }

    printf("Данные успешно записаны в файл %s\n", filename);

    // Закрытие файла после записи
    fclose(file);

    // Открытие файла для чтения и записи в бинарном режиме
    file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    // Чтение данных из бинарного файла и вывод на экран
    printf("Содержимое файла %s:\n", filename);
    for (int i = 0; i < count; i++) {
        fread(&num, sizeof(int), 1, file);
        printf("%d\n", num);
    }

    // Нахождение и вывод суммы максимального и минимального значений
    int sum = sum_max_min(filename, count);
    printf("Сумма максимального и минимального значений: %d\n", sum);

    // Зануление элементов по указанному принципу
    zero_elements(file, count);

    // Чтение зануленных данных из файла и вывод на экран
    fseek(file, 0, SEEK_SET);
    printf("\nФайл после зануления элементов:\n");
    for (int i = 0; i < count; i++) {
        fread(&num, sizeof(int), 1, file);
        printf("%d ", num);
    }
    printf("\n");

    // Закрытие файла после зануления
    fclose(file);

    // Удаление всех нулей из файла
    remove_zeros(filename);

    // Открытие файла для чтения после удаления нулей
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    // Чтение данных из файла без нулей и вывод на экран
    printf("\nФайл после удаления нулей:\n");
    while (fread(&num, sizeof(int), 1, file)) {
        printf("%d ", num);
    }
    printf("\n");

    // Закрытие файла после удаления нулей
    fclose(file);

    return 0;
}
