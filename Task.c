#include <stdio.h>
#include <locale.h>
#include "analysis.h"


// Главная функция
int main() {
    setlocale(LC_CTYPE, "RUS");
    int v;
    double x, y, eps, a, b, step, n;
    double found_x;

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
            printf("Введите с какой точностью: ");
            scanf("%lf", &n);
            printf("Интеграл = %lf\n", integral(a, b, n));
            break;

        case 4:
            printf("Введите y: ");
            scanf("%lf", &y);
            printf("Введите точность: ");
            scanf("%lf", &eps);
            printf("Поиск x для y = %.3lf\n", y);

            found_x = poisk_x(y, eps);
            printf("Результат поиска: x = %.4lf, f(x) = %.6lf\n", found_x, f(found_x));
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
