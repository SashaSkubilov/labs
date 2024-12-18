#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
int fillingstr() {





 }
void removeExtraSpaces(char* str) {
    int i = 0, j = 0;
    int inSpaces = 0; // Флаг для отслеживания пробелов

    while (str[i]) {
        // Если текущий символ не пробел
        if (str[i] != ' ') {
            str[j++] = str[i];
            inSpaces = 0; // Сбрасываем флаг пробелов
        }
        else if (inSpaces == 0) {
            // Если это первый пробел после слова
            str[j++] = ' ';
            inSpaces = 1; // Устанавливаем флаг пробелов
        }
        i++;
    }

    // Удаляем последний пробел, если он есть
    if (j > 0 && str[j - 1] == ' ') {
        j--;
    }

    str[j] = '\0'; // Завершаем строку
}

int main() {
    setlocale(LC_ALL, "rus");
    char* str = (char*)malloc(100 * sizeof(char)); // Динамическое выделение памяти

    if (str == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }

    printf("Введите строку: ");
    fgets(str, 100, stdin);

    removeExtraSpaces(str);

    printf("Строка без лишних пробелов: '%s'\n", str);

    free(str); // Освобождение выделенной памяти
    return 0;
}