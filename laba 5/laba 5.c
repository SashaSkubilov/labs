#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

// ������� ��� ����� ��������� � ��������� ������ (�������)
void filling2(float*** klava, int* rows, int* cols) {
    int check1 = 0;
    int a;
    float f;

    printf("������� ����� ����� �������: ");
    while (!check1) {
        check1 = scanf_s("%f", &f);
        while (getchar() != '\n');
        if (!check1) {
            printf("����������� ����.\n");
        }
        else {
            a = (int)f;
            if (a != f) {
                printf("������� ����� �����: ");
                check1 = 0;
            }
            else if (a < 1 || a > 100) {
                printf("������� ����� �� 1 �� 100 \n");
                check1 = 0;
            }
        }
    }
    *rows = a;

    printf("������� ����� �������� �������: ");
    int check0 = 0;
    int b;
    float by;
    while (!check0) {
        check0 = scanf_s("%f", &by);
        while (getchar() != '\n');
        if (!check0) {
            printf("����������� ����.\n");
        }
        else {
            b = (int)by;
            if (b != by) {
                printf("������� ����� �����: ");
                check0 = 0;
            }
            else if (b < 1 || b > 100) {
                printf("������� ����� �� 1 �� 100 \n");
                check0 = 0;
            }
        }
    }
    *cols = b;

    // �������� ������ ��� ����� �������
    *klava = (float**)malloc(*rows * sizeof(float*));
    for (int i = 0; i < *rows; i++) {
        // �������� ������ ��� �������� �������
        (*klava)[i] = (float*)malloc(*cols * sizeof(float));
    }

    // ������ �������� �������
    printf("���� ������ ��������� ������ ���������� ���������� ������� 1\n");
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
                printf("������� �������� �������� [%d][%d]: ", i, j);
                int check = 0;
                float x;
                while (!check) {
                    check = scanf_s("%f", &x);
                    while (getchar() != '\n');
                    if (!check) {
                        printf("����������� ����.\n");
                    }
                    else {
                        (*klava)[i][j] = x;
                        printf("�������� �������� [%d][%d] ����� = %f \n", i, j, x);
                    }
                }
            }
        }
    }
}

// ������� ��� ����� ��������� � ���������� ������
void filling1(float** klava, int* a2, int* a1) {
    int check1 = 0;
    int a;
    float f;

    printf("������� ������ �������: ");
    while (!check1) {
        check1 = scanf_s("%f", &f);
        while (getchar() != '\n');
        if (!check1) {
            printf("����������� ����.\n");
        }
        else {
            a = (int)f;
            if (a != f) {
                printf("������� ����� �����: ");
                check1 = 0;
            }
            else if (a < 1 || a > 100) {
                printf("������� ����� �� 1 �� 100 \n");
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
        printf("������� �������� �������: ");
        int check = 0;
        float x;
        while (!check) {
            check = scanf_s("%f", &x);
            while (getchar() != '\n');
            if (!check) {
                printf("����������� ����.\n");
            }
            else {
                (*klava)[i] = x;
                printf("�������� ����� = %f \n", x);
            }
        }
    }

    *a2 += a;
}

// ������� ��� �������� ����� ����� �� ����������� �������
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

// ���������� ������� 2 (�������� �������� ���������)

void work2(float** matrix, int rows, int cols) {
    int minDimension = rows < cols ? rows : cols;
    for (int i = 0; i < minDimension; i++) {
        matrix[i][cols - i - 1] = 0;
    }
    printf("������� ����� �������� �������� ���������:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void work3(void) {
    // ���������� ������� 3
}

// ������� ��� ������ �������
int check(void) {
    int w;
    float W;
    int check2 = 0;
    printf("�������� ����� ������� 1,2,3: ");
    while (!check2) {
        check2 = scanf_s("%f", &W);
        while (getchar() != '\n');
        if (!check2) {
            printf("����������� ����.\n");
        }
        else {
            w = (int)W;
            if (w != W) {
                printf("������� ����� �����");
                check2 = 0;
            }
            else if (w < 1 || w > 3) {
                printf("������� ����� 1,2,3 \n");
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
        printf("����� ������ (������ ����� � ��������� �������):\n");
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
        printf("������� %d x %d:\n", rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%f ", matrix[i][j]);
            }
            printf("\n");
        }
    }
    if (w == 3) {
            printf("������� ����������");
     
    }
    return 0;
}