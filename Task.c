#include <stdio.h>
#include <math.h>
#include <locale.h>

// Объявления функций
double f(double x);
double tochka(double x);
double tablica(double start, double end, double step);
double integral(double a, double b, int n);
double poisk_x(double y, double eps);
double proizvodnaya(double x);
void menu();

// Главная функция
int main() {
    setlocale(LC_CTYPE, "RUS");
    int v;
    double x, y, eps, a, b, step;
    int n;

    printf("\n");
    printf("****************************************\n");
    printf("*          АНАЛИЗ ФУНКЦИИ             *\n");
    printf("****************************************\n");
    printf("* f(x) = {                            *\n");
    printf("*   arctan(2x),         x < -2        *\n");
    printf("*   (e^x - x - 1)/x^2, -2 <= x < 0    *\n");
    printf("*   sqrt(x^2 + 4),      x >= 0        *\n");
    printf("****************************************\n");

    do {
        menu();
        printf("Выберите действие: ");
        scanf("%d", &v);

        switch (v) {
        case 1:
            printf("Введите x: ");
            scanf("%lf", &x);
            printf("f(%.3lf) = %.3lf\n", x, tochka(x));
            break;

        case 2:
            printf("Введите начало интервала: ");
            scanf("%lf", &a);
            printf("Введите конец интервала: ");
            scanf("%lf", &b);
            printf("Введите шаг: ");
            scanf("%lf", &step);
            tablica(a, b, step);
            break;

        case 3:
            printf("Введите начало интервала: ");
            scanf("%lf", &a);
            printf("Введите конец интервала: ");
            scanf("%lf", &b);
            printf("Введите количество прямоугольников: ");
            scanf("%d", &n);
            printf("Интеграл = %.6lf\n", integral(a, b, n));
            break;

        case 4:
            printf("Введите y: ");
            scanf("%lf", &y);
            printf("Введите точность: ");
            scanf("%lf", &eps);
            poisk_x(y, eps);
            break;

        case 5:
            printf("Введите x: ");
            scanf("%lf", &x);
            printf("f'(%.3lf) = %.6lf\n", x, proizvodnaya(x));
            break;

        case 6:
            printf("Выход\n");
            break;

        default:
            printf("Ошибка выбора\n");
            break;
        }

        if (v != 6) {
            printf("Продолжить? (1 - да, 0 - нет): ");
            scanf("%d", &v);
        }

    } while (v != 6 && v != 0);

    return 0;
}

// Основная функция f(x)
double f(double x) {
    if (x < -2.0) {
        return atan(2.0 * x);
    }
    else if (x < 0.0) {
        // Простая проверка на ноль
        if (x > -0.000001 && x < 0.000001) {
            return 0.5;
        }
        return (exp(x) - x - 1.0) / (x * x);
    }
    else {
        return sqrt(x * x + 4.0);
    }
}

// Меню
void menu() {
    printf("\n========================================\n");
    printf("| 1. Значение функции в точке          |\n");
    printf("| 2. Таблица значений                  |\n");
    printf("| 3. Вычисление интеграла              |\n");
    printf("| 4. Поиск x по y                      |\n");
    printf("| 5. Производная в точке               |\n");
    printf("| 6. Выход                             |\n");
    printf("========================================\n");
}

// 1. Значение в точке
double tochka(double x) {
    return f(x);
}

// 2. Таблица значений
double tablica(double start, double end, double step) {
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

// 3. Интеграл методом прямоугольников
double integral(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }

    return sum * h;
}

// 4. Поиск x по y
double poisk_x(double y, double eps) {
    printf("Поиск x для y = %.3lf\n", y);
    int found = 0;

    for (double x = -10.0; x <= 10.0; x += 0.001) {
        double fx = f(x);
        double diff = fx - y;
        if (diff < 0) diff = -diff;

        if (diff < eps) {
            printf("Найдено: x = %.4lf, f(x) = %.6lf\n", x, fx);
            found = 1;
        }
    }

    if (!found) {
        printf("Не найдено\n");
    }

    return 0;
}

// 5. Производная
double proizvodnaya(double x) {
    double h = 0.000001;
    return (f(x + h) - f(x)) / h;
}