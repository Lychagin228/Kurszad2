#include <stdio.h>
#include <math.h>
#include <locale.h>
#include "analysis.h"

/**
 * Основная функция f(x) - вычисление кусочной функции
 * @param x аргумент функции
 * @return значение функции в точке x
 */
double f(double x) {
    if (x < -2.0) {
        return atan(2.0 * x);
    }
    else if (x < 0.0) {
        return (exp(x) - x - 1.0) / (x * x);
    }
    else {
        return sqrt(x * x + 4.0);
    }
}

/**
 * Меню программы - вывод доступных операций
 * @return 0 в случае успешного выполнения
 */
int menu() {
    printf("\n========================================\n");
    printf("| 1. Значение функции в точке          |\n");
    printf("| 2. Таблица значений                  |\n");
    printf("| 3. Вычисление интеграла              |\n");
    printf("| 4. Поиск x по y                      |\n");
    printf("| 5. Производная в точке               |\n");
    printf("| 6. Выход                             |\n");
    printf("========================================\n");

    return 0;
}

/**
 * Функция вычисления значения в точке (обертка для меню)
 * @param x аргумент функции
 * @return значение функции f(x) в точке x
 */
double tochka(double x) {
    return f(x);
}

/**
 * Табулирование функции на интервале
 * @param start начало интервала
 * @param end конец интервала
 * @param step шаг табуляции
 * @return 0 в случае успешного выполнения
 */
int tablica(double start, double end, double step) {
    printf("\nТаблица:\n");
    printf("+----------+----------+\n");
    printf("|    x     |   f(x)   |\n");
    printf("+----------+----------+\n");

    for (double x = start; x <= end; x += step) {
        printf("| %8.3lf | %8.3lf |\n", x, f(x));
    }

    printf("+----------+----------+\n");
    return 0;
}

/**
 * Вычисление интеграла методом прямоугольников
 * @param a нижний предел интегрирования
 * @param b верхний предел интегрирования
 * @param n параметр, обратный количеству разбиений
 * @return приближенное значение интеграла
 */
double integral(double a, double b, double n) {
    double h = (b - a) * n;
    double sum = 0.0;

    for (int i = 0; i < pow(n, (-1.0)); i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }

    return sum * h;
}

/**
 * Поиск x по заданному y методом перебора
 * @param y целевое значение функции
 * @param eps допустимая погрешность
 * @return найденное значение x или 0.0 если не найдено
 */
double poisk_x(double y, double eps) {
    for (double x = -10.0; x <= 10.0; x += 0.001) {
        double fx = f(x);
        double diff = fx - y;
        if (diff < 0) diff = -diff;

        if (diff < eps) {
            return x;
        }
    }

    return 0.0;
}

/**
 * Вычисление производной методом правой разности
 * @param x точка, в которой вычисляется производная
 * @return приближенное значение производной
 */
double proizvodnaya(double x) {
    double h = 0.000001;
    return (f(x + h) - f(x)) / h;
}