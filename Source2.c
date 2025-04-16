#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// ��������� ������� ��� �������
void task1(); // ������ � ��������
void task2(); // ������� ��� �������� � �������
void removeNewline(char* str);
int stringCompare(const char* str1, const char* str2);

// ������� ���� ���������
void mainMenu() {
    int choice;

    do {
        printf("\n������� ����:\n");
        printf("1. ������ � ��������\n");
        printf("2. ������ � �������\n");
        printf("3. �����\n");
        printf("�������� �������: ");

        while (scanf("%d", &choice) != 1) {
            printf("������! ������� �����: ");
            while (getchar() != '\n') {}
        }
        getchar(); // ������� ������� ����� ������

        switch (choice) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            printf("����� �� ���������.\n");
            break;
        default:
            printf("�������� �����. ���������� �����.\n");
        }
    } while (choice != 3);
}

// ������ � �������� (������� 1)
void task1() {
    typedef struct {
        char genre[50];
        int releaseYear;
    } AdditionalInfo;

    typedef struct {
        char title[100];
        int duration; // ������������ � �������
        AdditionalInfo additionalInfo;
    } Movie;

    Movie* movies = NULL;
    int movieCount = 0;
    int choice;

    do {
        printf("\n���� ������ � ��������:\n");
        printf("1. �������� �����\n");
        printf("2. ����������� ��� ������\n");
        printf("3. ����� ����� �� ��������\n");
        printf("4. ������� ������ � ������������� ������ ��������\n");
        printf("5. ����� � ������� ����\n");
        printf("�������� ��������: ");

        while (scanf("%d", &choice) != 1) {
            printf("������! ������� �����: ");
            while (getchar() != '\n') {}
        }
        getchar(); // ������� ������� ����� ������

        switch (choice) {
        case 1: {
            movies = (Movie*)realloc(movies, (movieCount + 1) * sizeof(Movie));
            if (movies == NULL) {
                printf("������ ��������� ������!\n");
                return;
            }
            printf("\n������� �������� ������: ");
            fgets(movies[movieCount].title, sizeof(movies[movieCount].title), stdin);
            removeNewline(movies[movieCount].title);

            printf("������� ������������ ������ (� �������): ");
            while (scanf("%d", &movies[movieCount].duration) != 1) {
                printf("������! ������� �����: ");
                while (getchar() != '\n') {}
            }
            getchar();

            printf("������� ���� ������: ");
            fgets(movies[movieCount].additionalInfo.genre, sizeof(movies[movieCount].additionalInfo.genre), stdin);
            removeNewline(movies[movieCount].additionalInfo.genre);

            printf("������� ��� ������� ������: ");
            while (scanf("%d", &movies[movieCount].additionalInfo.releaseYear) != 1) {
                printf("������! ������� �����: ");
                while (getchar() != '\n') {}
            }
            getchar();

            movieCount++;
            break;
        }
        case 2:
            if (movieCount == 0) {
                printf("\n��� ��������� �������.\n");
            }
            else {
                for (int i = 0; i < movieCount; i++) {
                    printf("\n����� %d:\n", i + 1);
                    printf("��������: %s\n", movies[i].title);
                    printf("������������: %d �����\n", movies[i].duration);
                    printf("����: %s\n", movies[i].additionalInfo.genre);
                    printf("��� �������: %d\n", movies[i].additionalInfo.releaseYear);
                }
            }
            break;
        case 3:
            if (movieCount > 0) {
                char searchTitle[100];
                printf("\n������� �������� ������ ��� ������: ");
                fgets(searchTitle, sizeof(searchTitle), stdin);
                removeNewline(searchTitle);

                int found = 0;
                for (int i = 0; i < movieCount; i++) {
                    if (stringCompare(movies[i].title, searchTitle) == 0) {
                        printf("\n��������� �����:\n");
                        printf("��������: %s\n", movies[i].title);
                        printf("������������: %d �����\n", movies[i].duration);
                        printf("����: %s\n", movies[i].additionalInfo.genre);
                        printf("��� �������: %d\n", movies[i].additionalInfo.releaseYear);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("����� � ��������� \"%s\" �� ������.\n", searchTitle);
                }
            }
            else {
                printf("\n��� ��������� �������.\n");
            }
            break;
        case 4:
            if (movieCount > 0) {
                int maxDuration;
                printf("\n������� ������������ ������������ ������ ��� ��������: ");
                while (scanf("%d", &maxDuration) != 1) {
                    printf("������! ������� �����: ");
                    while (getchar() != '\n') {}
                }
                getchar();

                Movie* filteredMovies = (Movie*)malloc(movieCount * sizeof(Movie));
                if (filteredMovies == NULL) {
                    printf("������ ��������� ������!\n");
                    break;
                }

                int newCount = 0;
                for (int i = 0; i < movieCount; i++) {
                    if (movies[i].duration <= maxDuration) {
                        filteredMovies[newCount++] = movies[i];
                    }
                }

                free(movies);
                movies = filteredMovies;
                movieCount = newCount;

                printf("�������� ���������.\n");
            }
            else {
                printf("\n��� ��������� ������� ��� ��������.\n");
            }
            break;
        case 5:
            printf("������� � ������� ����.\n");
            break;
        default:
            printf("�������� �����. ���������� �����.\n");
        }
    } while (choice != 5);

    free(movies);
}

// ��������� ��� �������� ����
typedef struct {
    unsigned sign : 1; // ������� ���� ��� ����� �����
} BitField;

// ������� ��� ����������� ����� ����� ����� ������� ����
void task2() {
    int number;
    printf("\n������� �����: ");
    while (scanf("%d", &number) != 1) {
        printf("������! ������� �����: ");
        while (getchar() != '\n') {}
    }

    BitField bf;
    bf.sign = (unsigned)(number >> (sizeof(int) * 8 - 1)); // ����������� ����� �����

    if (bf.sign) {
        printf("����� �������������.\n");
    }
    else if (number == 0) {
        printf("����� ����� ����.\n");
    }
    else {
        printf("����� �������������.\n");
    }
}
// ������� ��� �������� ������� ����� ������
void removeNewline(char* str) {
    while (*str) {
        if (*str == '\n') {
            *str = '\0';
            break;
        }
        str++;
    }
}

// ������� ��� ��������� �����
int stringCompare(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// ������� �������
int main() {
    setlocale(LC_ALL, "rus");
    mainMenu();
    return 0;
}
