#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Прототипы функций для заданий
void task1(); // Работа с фильмами
void task2(); // Задание для операций с числами
void removeNewline(char* str);
int stringCompare(const char* str1, const char* str2);

// Главное меню программы
void mainMenu() {
    int choice;

    do {
        printf("\nГлавное меню:\n");
        printf("1. Работа с фильмами\n");
        printf("2. Работа с числами\n");
        printf("3. Выход\n");
        printf("Выберите задание: ");

        while (scanf("%d", &choice) != 1) {
            printf("Ошибка! Введите число: ");
            while (getchar() != '\n') {}
        }
        getchar(); // Очистка символа новой строки

        switch (choice) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 3);
}

// Работа с фильмами (задание 1)
void task1() {
    typedef struct {
        char genre[50];
        int releaseYear;
    } AdditionalInfo;

    typedef struct {
        char title[100];
        int duration; // Длительность в минутах
        AdditionalInfo additionalInfo;
    } Movie;

    Movie* movies = NULL;
    int movieCount = 0;
    int choice;

    do {
        printf("\nМеню работы с фильмами:\n");
        printf("1. Добавить фильм\n");
        printf("2. Просмотреть все фильмы\n");
        printf("3. Найти фильм по названию\n");
        printf("4. Удалить фильмы с длительностью больше заданной\n");
        printf("5. Назад в главное меню\n");
        printf("Выберите действие: ");

        while (scanf("%d", &choice) != 1) {
            printf("Ошибка! Введите число: ");
            while (getchar() != '\n') {}
        }
        getchar(); // Очистка символа новой строки

        switch (choice) {
        case 1: {
            movies = (Movie*)realloc(movies, (movieCount + 1) * sizeof(Movie));
            if (movies == NULL) {
                printf("Ошибка выделения памяти!\n");
                return;
            }
            printf("\nВведите название фильма: ");
            fgets(movies[movieCount].title, sizeof(movies[movieCount].title), stdin);
            removeNewline(movies[movieCount].title);

            printf("Введите длительность фильма (в минутах): ");
            while (scanf("%d", &movies[movieCount].duration) != 1) {
                printf("Ошибка! Введите число: ");
                while (getchar() != '\n') {}
            }
            getchar();

            printf("Введите жанр фильма: ");
            fgets(movies[movieCount].additionalInfo.genre, sizeof(movies[movieCount].additionalInfo.genre), stdin);
            removeNewline(movies[movieCount].additionalInfo.genre);

            printf("Введите год выпуска фильма: ");
            while (scanf("%d", &movies[movieCount].additionalInfo.releaseYear) != 1) {
                printf("Ошибка! Введите число: ");
                while (getchar() != '\n') {}
            }
            getchar();

            movieCount++;
            break;
        }
        case 2:
            if (movieCount == 0) {
                printf("\nНет доступных фильмов.\n");
            }
            else {
                for (int i = 0; i < movieCount; i++) {
                    printf("\nФильм %d:\n", i + 1);
                    printf("Название: %s\n", movies[i].title);
                    printf("Длительность: %d минут\n", movies[i].duration);
                    printf("Жанр: %s\n", movies[i].additionalInfo.genre);
                    printf("Год выпуска: %d\n", movies[i].additionalInfo.releaseYear);
                }
            }
            break;
        case 3:
            if (movieCount > 0) {
                char searchTitle[100];
                printf("\nВведите название фильма для поиска: ");
                fgets(searchTitle, sizeof(searchTitle), stdin);
                removeNewline(searchTitle);

                int found = 0;
                for (int i = 0; i < movieCount; i++) {
                    if (stringCompare(movies[i].title, searchTitle) == 0) {
                        printf("\nНайденный фильм:\n");
                        printf("Название: %s\n", movies[i].title);
                        printf("Длительность: %d минут\n", movies[i].duration);
                        printf("Жанр: %s\n", movies[i].additionalInfo.genre);
                        printf("Год выпуска: %d\n", movies[i].additionalInfo.releaseYear);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Фильм с названием \"%s\" не найден.\n", searchTitle);
                }
            }
            else {
                printf("\nНет доступных фильмов.\n");
            }
            break;
        case 4:
            if (movieCount > 0) {
                int maxDuration;
                printf("\nВведите максимальную длительность фильма для удаления: ");
                while (scanf("%d", &maxDuration) != 1) {
                    printf("Ошибка! Введите число: ");
                    while (getchar() != '\n') {}
                }
                getchar();

                Movie* filteredMovies = (Movie*)malloc(movieCount * sizeof(Movie));
                if (filteredMovies == NULL) {
                    printf("Ошибка выделения памяти!\n");
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

                printf("Удаление завершено.\n");
            }
            else {
                printf("\nНет доступных фильмов для удаления.\n");
            }
            break;
        case 5:
            printf("Возврат в главное меню.\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 5);

    free(movies);
}

// Структура для битового поля
typedef struct {
    unsigned sign : 1; // Битовое поле для знака числа
} BitField;

// Функция для определения знака числа через битовое поле
void task2() {
    int number;
    printf("\nВведите число: ");
    while (scanf("%d", &number) != 1) {
        printf("Ошибка! Введите число: ");
        while (getchar() != '\n') {}
    }

    BitField bf;
    bf.sign = (unsigned)(number >> (sizeof(int) * 8 - 1)); // Определение знака числа

    if (bf.sign) {
        printf("Число отрицательное.\n");
    }
    else if (number == 0) {
        printf("Число равно нулю.\n");
    }
    else {
        printf("Число положительное.\n");
    }
}
// Функция для удаления символа новой строки
void removeNewline(char* str) {
    while (*str) {
        if (*str == '\n') {
            *str = '\0';
            break;
        }
        str++;
    }
}

// Функция для сравнения строк
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

// Главная функция
int main() {
    setlocale(LC_ALL, "rus");
    mainMenu();
    return 0;
}
