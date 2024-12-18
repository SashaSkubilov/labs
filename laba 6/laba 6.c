#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

// Функция для заполнения массива
void filling1(int** klava, int* a2, int* a1) {
    int check1 = 0;
    int a;
    float f;

    printf("Введите размер массива: ");
    while (!check1) {
        check1 = scanf_s("%f", &f);
        while (getchar() != '\n');
        if (!check1) {
            printf("Некорректный ввод.\n");
        }
        else {
            a = (int)f;
            if (a != f) {
                printf("Введите целое число: ");
                check1 = 0;
            }
            else if (a < 1 || a > 100) {
                printf("Введите число от 1 до 100\n");
                check1 = 0;
            }
        }
    }

    if (*a2 + a > *a1) {
        *a1 = *a2 + a;
        int* array = (int*)malloc(sizeof(int) * (*a1));
        if (array == NULL) {
            return;
        }
        else {
            for (int i = 0; i < *a2; i++) {
                array[i] = (*klava)[i];
            }
        }
        free(*klava);
        *klava = array;
    }

    printf("Если хотите заполнить массив случайными значениями, нажмите 1\n");
    int z;
    scanf_s("%d", &z);
    if (z == 1) {
        for (int i = *a2; i < *a2 + a; i++) {
            (*klava)[i] = (rand() % 101) - 50;
        }
    }
    else {
        for (int i = *a2; i < *a2 + a; i++) {
            printf("Введите значение массива: ");
            int check = 0;
            float x;
            while (!check) {
                check = scanf_s("%f", &x);
                while (getchar() != '\n');
                if (!check) {
                    printf("Некорректный ввод.\n");
                }
                else {
                    (*klava)[i] = (int)x;
                    printf("Значение равно = %f\n", x);
                }
            }
        }
    }
    *a2 += a;
}

// Функция для выбора задания
int check(void) {
    int w;
    float W;
    int check2 = 0;
    printf("Выберите номер задания 1, 2, 3: ");
    while (!check2) {
        check2 = scanf_s("%f", &W);
        while (getchar() != '\n');
        if (!check2) {
            printf("Некорректный ввод.\n");
        }
        else {
            w = (int)W;
            if (w != W) {
                printf("Введите целое число: ");
                check2 = 0;
            }
            else if (w < 1 || w > 3) {
                printf("Введите число 1, 2, 3\n");
                check2 = 0;
            }
        }
    }
    return w;
}

// Функция для сортировки пузырьком нечетных отрицательных
void sort(int* klava, int a2) {
    int pos = 0;
    for (int i = 0; i < a2; i++) {
        if (klava[i] < 0 && klava[i] % 2 != 0) {

        }
        else {
            klava[i] = 0;
        }
    }
    for (int i = 0; i < a2 - 1; i++) {
        pos = i;
        for (int j = i + 1; j < a2; j++) {
            if (klava[pos] < klava[j]) {
                pos = j;
            }
        }
        if (pos != i) {
            int t = klava[i];
            klava[i] = klava[pos];
            klava[pos] = t;
        }
    }
}

int main(void) {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    int a1 = 1;
    int a2 = 0;
    int* klava = (int*)malloc(sizeof(int) * a1);

    int w = check();

    if (w == 1) {
        filling1(&klava, &a2, &a1);
        printf("a2 = %d, a1 = %d\n", a2, a1);
        for (int i = 0; i < a2; i++) {
            printf("%d ", klava[i]);
        }
        printf("\n");

        // Вызов функции сортировки
        sort(klava, a2);
        printf("Массив после сортировки отрицательных нечетных элементов: ");
        for (int i = 0; i < a2; i++) {
            printf("%d ", klava[i]);
        }
        printf("\n");

        free(klava);
    }

    return 0;
}

