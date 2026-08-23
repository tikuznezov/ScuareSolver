#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

// погрешность приравнивания к нулю
const double EPS = (0.0000000000001);

int SqEqSolve(Coefficient *coef, Roots *result)
{
    assert (coef);
    assert (result);

    result->count_roots = 2;
    // проверки
    if (Equal(coef->a, 0))
    {
        if (Equal(coef->b, 0))
        {
            if (Equal(coef->c, 0))
            {
                result->count_roots = INF_SOLUTIONS;
                return 0;
            }
            else // с != 0:
            {
            result->count_roots = NO_SOLUTIONS;
            return 0;
            }
        }

        else // b != 0:
        {
            LinEqSolve(coef, result);
            return 0;
        }
    }

    // a != 0
    double discriminant = (coef->b * coef->b) - (4 * coef->a * coef->c);
    if (discriminant < 0) // проверка, что дискриминант положительный
    {
        // printf("Discriminant < 0, roots not defined\n");
        // result[x1] = result[x2] = NULL;
        result->count_roots = NO_SOLUTIONS;
        return 0;
    }
    double sqrt_disc = sqrt(discriminant);

    result->x1 = ((-coef->b) + sqrt_disc) / (2 * coef->a);
    result->x2 = ((-coef->b) - sqrt_disc) / (2 * coef->a);

    if (Equal(result->x1, result->x2))
    {
        result->count_roots = 1; result->x2 = NAN;
        result->count_roots = ONE_SOLUTION;
    }
    return 0;
}


int LinEqSolve(Coefficient *coef, Roots *result)
{
    assert (result);
    assert (coef);
    if (coef->b == 0)
    {
        result->count_roots = NO_SOLUTIONS;
        return 0;
    }
    result->count_roots = ONE_SOLUTION;
    result->x1 = (- coef->c) / coef->b;
    return 0;
}


void PrintSqEqRoots(Roots *result)
{
    assert (result);
    GREEN

    switch (result->count_roots)
    {
    case ONE_SOLUTION:
        printf("Единственный корень: %lf\n", result->x1);
        DEF_COL
        return;
    case TWO_SOLUTIONS:
        printf("Два корня: x1 = %lf, x2 = %lf\n", result->x1, result->x2);
        DEF_COL
        return;
    case INF_SOLUTIONS:
        printf("Решением является любое число\n");
        DEF_COL
        return;
    case NO_SOLUTIONS:
        printf("Нет решений\n");
        DEF_COL
        return;
    }
    DEF_COL
    return;
}

// Сравнивает два числа double и выводит 1 если они равны, 0 если различны
int Equal(double a, double b)
{
    return (fabs(a - b) < EPS);
}


int SolveFromFile(FILE *file)
{
    int max_read_line = MAX_LINE;
    int error = 0;
    char check_eof;

    Coefficient coef_from_file = {};
    Roots roots_from_file = {};

    int num_of_eq = 0;
    while (num_of_eq++ < MAX_NUM_OF_EQ)
    {
        // Получаем коэффициенты и считываем конец файла
        check_eof = fscanf(file, "%lf; %lf; %lf", &coef_from_file.a, &coef_from_file.b, &coef_from_file.c);

        // решаем уравнение, получаем ошибки
        error = SqEqSolve(&coef_from_file, &roots_from_file);

        if (check_eof == EOF)
            return 0;

        else if (error != 0)
        {
            Output(error, &roots_from_file);
            return 1;
            break;
        }

        else
        {
            // Выводим коэффициенты
            PrintCoefs(&coef_from_file);
            Output(error, &roots_from_file);
            printf("\n");
        }
    }
    return 0;
}
