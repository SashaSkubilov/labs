#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

// Функция для ввода элементов в двумерный массив (матрицу)
void filling2(float*** klava, int* rows, int* cols) {
    int check1 = 0;
    int a;
    float f;

    printf("введите число строк матрицы: ");
    while (!check1) {
        check1 = scanf_s("%f", &f);
        while (getchar() != '\n');
        if (!check1) {
            printf("некоректный ввод.\n");
        }
        else {
            a = (int)f;
            if (a != f) {
                printf("введите целое число: ");
                check1 = 0;
            }
            else if (a < 1 || a > 100) {
                printf("введите число от 1 до 100 \n");
                check1 = 0;
            }
        }
    }
    *rows = a;

    printf("введите число столбцов матрицы: ");
    int check0 = 0;
    int b;
    float by;
    while (!check0) {
        check0 = scanf_s("%f", &by);
        while (getchar() != '\n');
        if (!check0) {
            printf("некоректный ввод.\n");
        }
        else {
            b = (int)by;
            if (b != by) {
                printf("введите целое число: ");
                check0 = 0;
            }
            else if (b < 1 || b > 100) {
                printf("введите число от 1 до 100 \n");
                check0 = 0;
            }
        }
    }
    *cols = b;

    // Выделяем память для строк матрицы
    *klava = (float**)malloc(*rows * sizeof(float*));
    for (int i = 0; i < *rows; i++) {
        // Выделяем память для столбцов матрицы
        (*klava)[i] = (float*)malloc(*cols * sizeof(float));
    }

    // Вводим значения матрицы
    printf("если хотите заполнить массив случайными значениями нажмите 1\n");
    int z;
    scanf_s("%d", &z);
    if (z == 1) {
        for (int i = 0; i < *rows; i++) {
            for (int j = 0; j < *cols; j++) {
                (*klava)[i][j] = rand() % 101;
            }
        }
    }
    else {
        for (int i = 0; i < *rows; i++) {
            for (int j = 0; j < *cols; j++) {
                printf("введите значение элемента [%d][%d]: ", i, j);
                int check = 0;
                float x;
                while (!check) {
                    check = scanf_s("%f", &x);
                    while (getchar() != '\n');
                    if (!check) {
                        printf("некоректный ввод.\n");
                    }
                    else {
                        (*klava)[i][j] = x;
                        printf("значение элемента [%d][%d] равно = %f \n", i, j, x);
                    }
                }
            }
        }
    }
}

// Функция для ввода элементов в одномерный массив
void filling1(float** klava, int* a2, int* a1) {
    int check1 = 0;
    int a;
    float f;

    printf("введите размер массива: ");
    while (!check1) {
        check1 = scanf_s("%f", &f);
        while (getchar() != '\n');
        if (!check1) {
            printf("некоректный ввод.\n");
        }
        else {
            a = (int)f;
            if (a != f) {
                printf("введите целое число: ");
                check1 = 0;
            }
            else if (a < 1 || a > 100) {
                printf("введите число от 1 до 100 \n");
                check1 = 0;
            }
        }
    }

    if (*a2 + a > *a1) {
        *a1 = *a2 + a;
        float* array = (float*)malloc(sizeof(float) * *a1);
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

    for (int i = *a2; i < *a2 + a; i++) {
        printf("введите значение массива: ");
        int check = 0;
        float x;
        while (!check) {
            check = scanf_s("%f", &x);
            while (getchar() != '\n');
            if (!check) {
                printf("некоректный ввод.\n");
            }
            else {
                (*klava)[i] = x;
                printf("значение равно = %f \n", x);
            }
        }
    }

    *a2 += a;
}

// Функция для удаления целых чисел из одномерного массива
void work1(const float* arr, int size, float** result, int* newSize) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if ((int)arr[i] != arr[i]) {
            count++;
        }
    }
    *result = (float*)malloc(sizeof(float) * count);
    if (*result == NULL) {
        *newSize = 0;
        return;
    }
    int index = 0;
    for (int i = 0; i < size; i++) {
        if ((int)arr[i] != arr[i]) {
            (*result)[index++] = arr[i];
        }
    }
    *newSize = count;
}

// Реализация задания 2 (удаление побочной диагонали)

void work2(float** matrix, int rows, int cols) {
    int minDimension = rows < cols ? rows : cols;
    for (int i = 0; i < minDimension; i++) {
        matrix[i][cols - i - 1] = 0;
    }
    printf("Матрица после удаления побочной диагонали:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void work3(void) {
    // Реализация задания 3
}

// Функция для выбора задания
int check(void) {
    int w;
    float W;
    int check2 = 0;
    printf("выберите номер задания 1,2,3: ");
    while (!check2) {
        check2 = scanf_s("%f", &W);
        while (getchar() != '\n');
        if (!check2) {
            printf("некоректный ввод.\n");
        }
        else {
            w = (int)W;
            if (w != W) {
                printf("введите целое число");
                check2 = 0;
            }
            else if (w < 1 || w > 3) {
                printf("введите число 1,2,3 \n");
                check2 = 0;
            }
        }
    }
    return w;
}

int main(void) {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    int a1 = 1;
    int a2 = 0;
    float* klava = (float*)malloc(sizeof(float) * a1);
    int w = check();

    if (w == 1) {
        filling1(&klava, &a2, &a1);
        printf("a2 = %d, a1 = %d\n", a2, a1);
        for (int i = 0; i < a2; i++) {
            printf("%f ", klava[i]);
        }
        printf("\n");
        int newSize;
        float* newArr;
        work1(klava, a2, &newArr, &newSize);
        printf("Новый массив (только числа с плавающей запятой):\n");
        for (int i = 0; i < newSize; i++) {
            printf("%f ", newArr[i]);
        }
        printf("\n");
        free(newArr);
    }
    if (w == 2) {
        int rows, cols;
        float** matrix;
        filling2(&matrix, &rows, &cols);
        printf("Матрица %d x %d:\n", rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%f ", matrix[i][j]);
            }
            printf("\n");
        }
    }
    if (w == 3) {
            printf("задание недоступно");
     
    }
    return 0;
}