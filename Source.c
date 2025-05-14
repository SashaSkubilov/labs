#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define INPUT_BUFFER_SIZE 100

// ==================== ���������� ������� ====================
typedef struct {
    char* items;
    int front;
    int rear;
    int size;
    int capacity;
} CharQueue;

void initQueue(CharQueue* q, int capacity) {
    q->items = (char*)malloc(capacity * sizeof(char));
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = capacity;
}

void freeQueue(CharQueue* q) {
    free(q->items);
}

bool isEmptyQueue(CharQueue* q) {
    return q->size == 0;
}

bool isFullQueue(CharQueue* q) {
    return q->size == q->capacity;
}

bool enqueue(CharQueue* q, char c) {
    if (isFullQueue(q)) {
        printf("������� �����������!\n");
        return false;
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->items[q->rear] = c;
    q->size++;
    return true;
}

bool dequeue(CharQueue* q, char* c) {
    if (isEmptyQueue(q)) {
        printf("������� �����!\n");
        return false;
    }

    *c = q->items[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return true;
}

char getFirstQueue(CharQueue* q) {
    if (isEmptyQueue(q)) {
        return '\0';
    }
    return q->items[q->front];
}

char getLastQueue(CharQueue* q) {
    if (isEmptyQueue(q)) {
        return '\0';
    }
    return q->items[q->rear];
}

// �������� �������������� �������
bool isSymmetric(CharQueue* q) {
    if (isEmptyQueue(q)) return true;

    // ���������� ��� ��������� ��� ��������� ���������
    int left = q->front;
    int right = q->rear;
    int count = 0;

    while (count < q->size / 2) {
        if (q->items[left] != q->items[right]) {
            return false;
        }
        left = (left + 1) % q->capacity;
        right = (right - 1 + q->capacity) % q->capacity;
        count++;
    }

    return true;
}

// ==================== ���������� ���� ====================
typedef struct {
    char* items;
    int front;
    int rear;
    int size;
    int capacity;
} CharDeque;

void initDeque(CharDeque* dq, int capacity) {
    dq->items = (char*)malloc(capacity * sizeof(char));
    dq->front = -1;
    dq->rear = 0;
    dq->size = 0;
    dq->capacity = capacity;
}

void freeDeque(CharDeque* dq) {
    free(dq->items);
}

bool isEmptyDeque(CharDeque* dq) {
    return dq->size == 0;
}

bool isFullDeque(CharDeque* dq) {
    return dq->size == dq->capacity;
}

char getFrontDeque(CharDeque* dq) {
    if (isEmptyDeque(dq)) return '\0';
    return dq->items[dq->front];
}

char getRearDeque(CharDeque* dq) {
    if (isEmptyDeque(dq)) return '\0';
    return dq->items[dq->rear];
}

bool pushFront(CharDeque* dq, char c) {
    if (isFullDeque(dq)) {
        printf("��� ����������!\n");
        return false;
    }

    if (!isEmptyDeque(dq) && c == getRearDeque(dq)) {
        printf("����������! ������� �� ��������������� �����: %c\n", getRearDeque(dq));
    }

    if (isEmptyDeque(dq)) {
        dq->front = 0;
        dq->rear = 0;
    }
    else {
        dq->front = (dq->front - 1 + dq->capacity) % dq->capacity;
    }

    dq->items[dq->front] = c;
    dq->size++;
    return true;
}

bool pushRear(CharDeque* dq, char c) {
    if (isFullDeque(dq)) {
        printf("��� ����������!\n");
        return false;
    }

    if (!isEmptyDeque(dq) && c == getFrontDeque(dq)) {
        printf("����������! ������� �� ��������������� �����: %c\n", getFrontDeque(dq));
    }

    if (isEmptyDeque(dq)) {
        dq->front = 0;
        dq->rear = 0;
    }
    else {
        dq->rear = (dq->rear + 1) % dq->capacity;
    }

    dq->items[dq->rear] = c;
    dq->size++;
    return true;
}

bool popFront(CharDeque* dq, char* c) {
    if (isEmptyDeque(dq)) {
        printf("��� ����!\n");
        return false;
    }

    *c = dq->items[dq->front];
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    }
    else {
        dq->front = (dq->front + 1) % dq->capacity;
    }
    dq->size--;
    return true;
}

bool popRear(CharDeque* dq, char* c) {
    if (isEmptyDeque(dq)) {
        printf("��� ����!\n");
        return false;
    }

    *c = dq->items[dq->rear];
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    }
    else {
        dq->rear = (dq->rear - 1 + dq->capacity) % dq->capacity;
    }
    dq->size--;
    return true;
}

// ==================== ����� ������� ====================
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

bool getSingleCharInput(char* c) {
    char input[INPUT_BUFFER_SIZE];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return false;
    }

    if (strlen(input) != 2 || input[1] != '\n') {
        printf("������: ������� ����� ���� ������!\n");
        clearInputBuffer();
        return false;
    }

    *c = input[0];
    return true;
}

// ==================== ������� ��� ������ � �������� ====================
void inputToQueue(CharQueue* q) {
    printf("������� ������� �� ������ (��� ���������� ������� '0'):\n");

    char c;
    while (1) {
        printf("������� ������: ");

        if (!getSingleCharInput(&c)) {
            continue;
        }

        if (c == '0') {
            break;
        }

        if (!isEmptyQueue(q) && c == getLastQueue(q)) {
            printf("���������� � ��������� ���������! ������ �������: %c\n", getFirstQueue(q));
        }

        if (!enqueue(q, c)) {
            printf("������� ���������, ���������� �������� ������ ��������.\n");
            break;
        }
    }
}

void printQueue(CharQueue* q) {
    if (isEmptyQueue(q)) {
        printf("������� �����!\n");
        return;
    }

    printf("���������� �������: ");

    int i = q->front;
    for (int count = 0; count < q->size; count++) {
        printf("%c ", q->items[i]);
        i = (i + 1) % q->capacity;
    }
    printf("\n");
}

// ==================== ������� ��� ������ � ����� ====================
void inputToDeque(CharDeque* dq) {
    printf("������� ������� �� ������ (��� ���������� ������� '0'):\n");

    char c;
    bool addToFront = true;
    while (1) {
        printf("������� ������: ");
        if (!getSingleCharInput(&c)) continue;

        if (c == '0') break;

        if (addToFront) {
            if (!pushFront(dq, c)) break;
            printf("�������� � ������: %c\n", c);
        }
        else {
            if (!pushRear(dq, c)) break;
            printf("�������� � �����: %c\n", c);
        }
        addToFront = !addToFront;
    }
}

void printDeque(CharDeque* dq) {
    if (isEmptyDeque(dq)) {
        printf("��� ����!\n");
        return;
    }

    printf("���������� ����: ");
    int i = dq->front;
    for (int count = 0; count < dq->size; count++) {
        printf("%c ", dq->items[i]);
        i = (i + 1) % dq->capacity;
    }
    printf("\n");
}

// ==================== ������� ���� ====================
int main() {
    setlocale(LC_ALL, "rus");
    int choice;

    do {
        printf("\n�������� ���������:\n");
        printf("1. ������ � ��������\n");
        printf("2. ������ � �����\n");
        printf("3. �����\n");
        printf("��� �����: ");
        if (scanf_s("%d", &choice) != 1) {
            printf("������ �����!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1: {
            int size;
            printf("������� ������ �������: ");
            if (scanf_s("%d", &size) != 1 || size <= 0) {
                printf("�������� ������!\n");
                clearInputBuffer();
                break;
            }
            clearInputBuffer();

            CharQueue q;
            initQueue(&q, size);
            inputToQueue(&q);
            printQueue(&q);

            if (isSymmetric(&q)) {
                printf("������� �����������!\n");
            }
            else {
                printf("������� �� �����������.\n");
            }

            freeQueue(&q);
            break;
        }
        case 2: {
            int size;
            printf("������� ������ ����: ");
            if (scanf_s("%d", &size) != 1 || size <= 0) {
                printf("�������� ������!\n");
                clearInputBuffer();
                break;
            }
            clearInputBuffer();

            CharDeque dq;
            initDeque(&dq, size);
            inputToDeque(&dq);
            printDeque(&dq);
            freeDeque(&dq);
            break;
        }
        case 3:
            printf("�����...\n");
            break;
        default:
            printf("�������� �����!\n");
        }
    } while (choice != 3);

    return 0;
}