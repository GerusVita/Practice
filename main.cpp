#include "stdio.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#define MAX N*N
int *dosc = NULL;
int length;
void path(int x, int y, int e1, int e2, int n, int hag);

int main() {
    unsigned int N, h, j, k;
    unsigned int s1, s2, e1, e2;
    setlocale(LC_ALL, "rus");
    printf("Введите размер доски  ");
    scanf("%i", &N);
    dosc = (int *) malloc(MAX * sizeof(int));
    length = MAX;
    srand((unsigned) time(0));
    for (int i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            *(dosc + N * i + j) = 255;
    h = rand() % (N * N) + 2;
    for (int i = 0; i <= h; i++) {
        j = rand() % N;
        k = rand() % N;
        *(dosc + N * j + k) = 0;
    }
    for (int i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (*(dosc + N * i + j) == 255)
                printf("*  ");
            else
                printf("0  ");
        }
        printf("\n");
    }

    printf("Введите начальные координаты:");
    do {
        scanf("%i%i", &s1, &s2);
        if (*(dosc + N * s1 + s2) != 0 || s1 > N || s2 > N)
            printf("Введите правильные координаты :");
    } while (*(dosc + N * s1 + s2) != 0);
    printf("Введите конечные координаты:");
    do {
        scanf("%i%i", &e1, &e2);
        if (*(dosc + N * e1 + e2) != 255 || e1 > N || e2 > N)
            printf("Введите корректные координаты :");
    } while (*(dosc + N * e1 + e2) != 255);
    path(s1, s2, e1, e2, N, 1);
    if (length == N * N)printf("Пути нет");
    else {
        printf("%i шагов\n", (length-1));
        for (int i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (*(dosc + N * i + j) == 0)
                    printf("o  ");
                else if (*(dosc + N * i + j) == 255)
                    printf("*  ");
                else
                    printf("+  ");
            }
            printf("\n");
        }
    }
    return 0;
}

void path(int x, int y, int e1, int e2, int n, int hag) {
    if (x == e1 && y == e2 && hag < length) {
        length = hag;
    } else {
        if (x > 0)
            if (dosc[n * (x - 1) + y] > hag) {
                dosc[n * (x - 1) + y] = hag;
                path(x - 1, y, e1, e2, n, hag + 1);
            }
        if (y > 0)
            if (dosc[n * x + (y - 1)] > hag) {
                dosc[n * x + (y - 1)] = hag;
                path(x, y - 1, e1, e2, n, hag + 1);
            }
        if (x < n - 1)
            if (dosc[n * (x + 1) + y] > hag) {
                dosc[n * (x + 1) + y] = hag;
                path(x + 1, y, e1, e2, n, hag + 1);
            }
        if (y < n - 1)
            if (dosc[n * x + (y + 1)] > hag) {
                dosc[n * x + (y + 1)] = hag;
                path(x, y + 1, e1, e2, n, hag + 1);
            }
    }
}