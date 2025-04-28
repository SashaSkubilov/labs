#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

typedef struct {
    int* data;
    int top;
    int capacity;
} Stack;

// Базовые функции стека
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

bool isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Стек заполнен!\n");
        return;
    }
    stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст!\n");
        return -1;
    }
    return stack->data[stack->top--];
}

void displayStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст\n");
        return;
    }
    printf("Содержимое стека: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

void freeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

// Функция для безопасного ввода целого числа
int safeInputInt(const char* prompt) {
    int value;
    char buffer[100];
    char* endptr;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Ошибка ввода!\n");
            continue;
        }

        value = strtol(buffer, &endptr, 10);

        if (endptr == buffer) {
            printf("Ошибка: Введите целое число!\n");
            continue;
        }

        // Проверка на лишние символы
        int hasExtraChars = 0;
        for (char* p = endptr; *p != '\0'; p++) {
            if (*p != '\n' && *p != ' ' && *p != '\t') {
                hasExtraChars = 1;
                break;
            }
        }

        if (hasExtraChars) {
            printf("Ошибка: Введены лишние символы!\n");
            continue;
        }

        break;
    }

    return value;
}

// Функция для безопасного ввода размера стека
int safeInputSize(const char* prompt) {
    int size;
    while (1) {
        size = safeInputInt(prompt);
        if (size <= 0) {
            printf("Размер должен быть положительным числом!\n");
            continue;
        }
        break;
    }
    return size;
}

// Функция для ввода элементов стека по возрастанию
void inputSortedStack(Stack* stack, const char* stackName) {
    printf("Заполнение стека %s (по возрастанию):\n", stackName);
    int prev = -2147483647 - 1; // Минимальное значение int

    for (int i = 0; i < stack->capacity; i++) {
        int val;
        while (1) {
            val = safeInputInt("Введите элемент (должен быть >= предыдущего): ");
            if (val >= prev) {
                prev = val;
                break;
            }
            printf("Ошибка: Элемент должен быть больше или равен предыдущему (%d)!\n", prev);
        }
        push(stack, val);
    }
}

// Функция для копирования стека
Stack* copyStack(Stack* original) {
    Stack* copy = createStack(original->capacity);
    Stack* temp = createStack(original->capacity);

    while (!isEmpty(original)) {
        push(temp, pop(original));
    }

    while (!isEmpty(temp)) {
        int val = pop(temp);
        push(original, val);
        push(copy, val);
    }

    freeStack(temp);
    return copy;
}

// Функция для объединения двух отсортированных стеков
Stack* mergeSortedStacks(Stack* s1, Stack* s2) {
    Stack* result = createStack(s1->capacity + s2->capacity);
    Stack* temp = createStack(s1->capacity + s2->capacity);

    // Пока оба стека не пусты
    while (!isEmpty(s1) && !isEmpty(s2)) {
        if (s1->data[s1->top] > s2->data[s2->top]) {
            push(temp, pop(s1));
        }
        else {
            push(temp, pop(s2));
        }
    }

    // Добавляем оставшиеся элементы из s1
    while (!isEmpty(s1)) {
        push(temp, pop(s1));
    }

    // Добавляем оставшиеся элементы из s2
    while (!isEmpty(s2)) {
        push(temp, pop(s2));
    }

    // Переносим из временного стека в результат (чтобы получить возрастающий порядок)
    while (!isEmpty(temp)) {
        push(result, pop(temp));
    }

    freeStack(temp);
    return result;
}

void mergeAndSortTask() {
    int capacity = safeInputSize("Введите размер стеков: ");

    Stack* s1 = createStack(capacity);
    Stack* s2 = createStack(capacity);

    inputSortedStack(s1, "первого");
    inputSortedStack(s2, "второго");

    Stack* s3 = mergeSortedStacks(copyStack(s1), copyStack(s2));

    printf("\nПервый стек (оригинальный, по возрастанию):\n");
    displayStack(s1);

    printf("Второй стек (оригинальный, по возрастанию):\n");
    displayStack(s2);

    printf("Третий стек (объединенный по возрастанию):\n");
    displayStack(s3);

    freeStack(s1);
    freeStack(s2);
    freeStack(s3);
}

// Функция для поиска самых частых элементов
void findMostFrequent(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст\n");
        return;
    }

    int max_count = 1;
    int* elements = (int*)malloc(stack->capacity * sizeof(int));
    int elements_count = 0;

    for (int i = 0; i <= stack->top; i++) {
        int count = 1;
        for (int j = i + 1; j <= stack->top; j++) {
            if (stack->data[i] == stack->data[j]) {
                count++;
            }
        }

        if (count > max_count) {
            max_count = count;
            elements_count = 0;
            elements[elements_count++] = stack->data[i];
        }
        else if (count == max_count) {
            // Проверяем, нет ли уже этого элемента в списке
            bool already_exists = false;
            for (int k = 0; k < elements_count; k++) {
                if (elements[k] == stack->data[i]) {
                    already_exists = true;
                    break;
                }
            }
            if (!already_exists) {
                elements[elements_count++] = stack->data[i];
            }
        }
    }

    if (max_count == 1) {
        printf("Все элементы уникальны\n");
    }
    else {
        printf("Самые частые элементы (встречаются %d раз(а)): ", max_count);
        for (int i = 0; i < elements_count; i++) {
            printf("%d ", elements[i]);
        }
        printf("\n");
    }

    free(elements);
}

void findRepeatingElements() {
    int capacity = safeInputSize("Введите размер стека: ");

    Stack* stack = createStack(capacity);

    int choice;
    do {
        printf("\nМеню:\n");
        printf("1. Добавить элемент\n");
        printf("2. Удалить элемент\n");
        printf("3. Показать стек\n");
        printf("4. Найти самые частые элементы\n");
        printf("0. Выход\n");
        printf("Выбор: ");

        choice = safeInputInt("");

        switch (choice) {
        case 1: {
            if (isFull(stack)) {
                printf("Стек заполнен!\n");
                break;
            }
            int value = safeInputInt("Введите значение: ");
            push(stack, value);
            break;
        }
        case 2: {
            int val = pop(stack);
            if (val != -1) {
                printf("Удалено: %d\n", val);
            }
            break;
        }
        case 3:
            displayStack(stack);
            break;
        case 4:
            findMostFrequent(stack);
            break;
        case 0:
            break;
        default:
            printf("Неверный выбор\n");
        }
    } while (choice != 0);

    freeStack(stack);
}

int main() {
    setlocale(LC_ALL, "rus");

    int choice;
    do {
        printf("\nГлавное меню:\n");
        printf("1. Поиск самых частых элементов в стеке\n");
        printf("2. Объединение и сортировка стеков (с вводом по возрастанию)\n");
        printf("0. Выход\n");
        printf("Выбор: ");

        choice = safeInputInt("");

        switch (choice) {
        case 1:
            findRepeatingElements();
            break;
        case 2:
            mergeAndSortTask();
            break;
        case 0:
            printf("Выход...\n");
            break;
        default:
            printf("Неверный выбор\n");
        }
    } while (choice != 0);

    return 0;
}