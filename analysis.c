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
 * @return choice в случае успешного выполнения
 */
int menu() {
    int choice;
    
    printf("\n========================================\n");
    printf("| 1. Значение функции в точке          |\n");
    printf("| 2. Таблица значений                  |\n");
    printf("| 3. Вычисление интеграла              |\n");
    printf("| 4. Поиск x по y                      |\n");
    printf("| 5. Производная в точке               |\n");
    printf("| 6. Выход                             |\n");
    printf("========================================\n");
    
    // Запрашиваем ввод до тех пор, пока не получим корректный выбор
    while (1) {
        printf("Выберите действие (1-6): ");
        
        // Проверяем, что введено именно число
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка: введите число!\n");
            // Очищаем буфер ввода
            while (getchar() != '\n');
            continue;
        }
        
        // Проверяем диапазон
        if (choice >= 1 && choice <= 6) {
            break; // Корректный ввод
        } else {
            printf("Ошибка: выберите число от 1 до 6!\n");
        }
    }
    
    return choice;
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
 * Вычисление определенного интеграла методом средних прямоугольников
 * @param a нижний предел интегрирования (начало интервала)
 * @param b верхний предел интегрирования (конец интервала)
 * @param n количество разбиений интервала (целое положительное число)
 * @return приближенное значение определенного интеграла
 */
double integral(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }

    return sum * h;
}

/**
 * Поиск аргумента x, при котором значение функции приближенно равно заданному y
 * @param y целевое значение функции, которое нужно найти
 * @param eps допустимая абсолютная погрешность сравнения |f(x) - y| < eps
 * @param result указатель на переменную для записи найденного значения x
 * @return 1 - если решение найдено, 0 - если решение не найдено на интервале [-10, 10]
 *         При успешном поиске результат записывается по адресу result
 */
int poisk_x(double y, double eps, double* result) {
    double start = -10.0;
    double end = 10.0;
    double step = 0.001;
    
    *result = 10000.0;
    
    for (double x = start; x <= end; x += step) {
        double fx = f(x);
        double diff = fabs(fx - y);

        if (diff < eps) {
            *result = x;
            return 1;
        }
    }
    
    return 0;
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
