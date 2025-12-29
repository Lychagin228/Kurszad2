#include <stdio.h>
#include <math.h>
#include "analysis.h"

// Определение глобальной переменной
double global_eps = 0.001;

// Основная функция f(x)
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

// Меню программы
int menu() {
    int choice;

    printf("\n========================================\n");
    printf("| 1. Значение функции в точке          |\n");
    printf("| 2. Таблица значений                  |\n");
    printf("| 3. Вычисление интеграла              |\n");
    printf("| 4. Поиск x по y                      |\n");
    printf("| 5. Производная в точке               |\n");
    printf("| 6. Изменить точность (текущ.: %.6lf) |\n", global_eps);
    printf("| 7. Выход                             |\n");
    printf("========================================\n");

    while (1) {
        printf("Выберите действие (1-7): ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка: введите число!\n");
            // Очищаем буфер ввода
            while (getchar() != '\n');
            continue;
        }

        // Проверяем диапазон
        if (choice >= 1 && choice <= 7) {
            break;
        }
        else {
            printf("Ошибка: выберите число от 1 до 7!\n");
        }
    }

    return choice;
}

// Табулирование функции на экран
int tablica(double start, double end, double step) {
    printf("\nТаблица значений функции:\n");
    printf("Интервал: [%.3lf, %.3lf], шаг: %.3lf\n", start, end, step);
    printf("+----------+----------+\n");
    printf("|    x     |   f(x)   |\n");
    printf("+----------+----------+\n");

    for (double x = start; x <= end; x += step) {
        printf("| %8.3lf | %8.3lf |\n", x, f(x));
    }

    printf("+----------+----------+\n");
    return 0;
}

// Табулирование функции в файл
int tablica_to_file(double start, double end, double step, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл '%s' для записи\n", filename);
        return 0;
    }

    fprintf(file, "Таблица значений функции f(x)\n");
    fprintf(file, "Интервал: [%.3lf, %.3lf], шаг: %.3lf\n", start, end, step);
    fprintf(file, "+----------+----------+\n");
    fprintf(file, "|    x     |   f(x)   |\n");
    fprintf(file, "+----------+----------+\n");

    for (double x = start; x <= end; x += step) {
        fprintf(file, "| %8.3lf | %8.3lf |\n", x, f(x));
    }

    fprintf(file, "+----------+----------+\n");
    fclose(file);
    printf("Таблица успешно сохранена в файл '%s'\n", filename);
    return 1;
}

// Табулирование функции и на экран, и в файл
int tablica_and_file(double start, double end, double step, const char* filename) {
    // Вывод на экран
    tablica(start, end, step);
    
    // Запись в файл
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл '%s' для записи\n", filename);
        return 0;
    }

    fprintf(file, "Таблица значений функции f(x)\n");
    fprintf(file, "Интервал: [%.3lf, %.3lf], шаг: %.3lf\n", start, end, step);
    fprintf(file, "+----------+----------+\n");
    fprintf(file, "|    x     |   f(x)   |\n");
    fprintf(file, "+----------+----------+\n");

    for (double x = start; x <= end; x += step) {
        fprintf(file, "| %8.3lf | %8.3lf |\n", x, f(x));
    }

    fprintf(file, "+----------+----------+\n");
    fclose(file);
    printf("Таблица также сохранена в файл '%s'\n", filename);
    return 1;
}

// Интеграл с заданным количеством разбиений
double integral_with_n(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }

    return sum * h;
}

// Интеграл с использованием глобальной точности
double integral_with_eps(double a, double b) {
    // Автоматический расчет количества разбиений на основе точности
    int n = (int)((b - a) / sqrt(global_eps));
    if (n < 1) n = 1;
    if (n > 1000000) n = 1000000; // Ограничение для производительности
    
    printf("Автоматически выбрано количество разбиений: %d\n", n);
    return integral_with_n(a, b, n);
}

// Запись результата интеграла в файл
int integral_to_file(double a, double b, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл '%s' для записи\n", filename);
        return 0;
    }

    double result = integral_with_eps(a, b);
    
    fprintf(file, "Результат вычисления интеграла\n");
    fprintf(file, "Функция: f(x) = кусочная функция\n");
    fprintf(file, "Интервал интегрирования: [%.3lf, %.3lf]\n", a, b);
    fprintf(file, "Используемая точность: %.6lf\n", global_eps);
    fprintf(file, "Метод: средние прямоугольники\n");
    fprintf(file, "Значение интеграла: %.6lf\n", result);
    
    fclose(file);
    printf("Результат интеграла сохранен в файл '%s'\n", filename);
    return 1;
}

// Поиск x по y
double poisk_x(double y, double eps, double start, double end, double step) {
    for (double x = start; x <= end; x += step) {
        double fx = f(x);
        double diff = fabs(fx - y);

        if (diff < eps) {
            return x;
        }
    }

    return 10000.0; // Специальное значение, обозначающее "не найдено"
}

// Запись результата поиска в файл
int poisk_x_to_file(double y, double eps, double start, double end, double step, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл '%s' для записи\n", filename);
        return 0;
    }

    double found_x = poisk_x(y, eps, start, end, step);
    
    fprintf(file, "Результат поиска аргумента x по значению функции y\n");
    fprintf(file, "Целевое значение y: %.6lf\n", y);
    fprintf(file, "Допустимая погрешность: %.6lf\n", eps);
    fprintf(file, "Интервал поиска: [%.3lf, %.3lf]\n", start, end);
    fprintf(file, "Шаг поиска: %.6lf\n", step);
    fprintf(file, "Метод: последовательный перебор\n");
    
    if (found_x != 10000.0) {
        fprintf(file, "Результат: НАЙДЕНО\n");
        fprintf(file, "x = %.6lf\n", found_x);
        fprintf(file, "f(%.6lf) = %.6lf\n", found_x, f(found_x));
    } else {
        fprintf(file, "Результат: НЕ НАЙДЕНО\n");
        fprintf(file, "Решение не найдено в заданном интервале с указанной точностью.\n");
    }
    
    fclose(file);
    printf("Результат поиска сохранен в файл '%s'\n", filename);
    return 1;
}

// Производная с использованием глобальной точности
double proizvodnaya(double x) {
    // Оптимальный шаг для численного дифференцирования
    double h = pow(global_eps, 1.0/3.0);
    if (h < 1e-10) h = 1e-10; // Минимальный шаг

    return (f(x + h) - f(x - h)) / (2.0 * h);
}




