#include "sqeq.h"

#define TEST_ERROR

// погрешность приравнивания к нулю
const double EPS = (0.001);

// решает квадратное уравнение
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
    return StandardSqEqSolve(coef, result);
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
        break;

    case TWO_SOLUTIONS:
        printf("Два корня: x1 = %lf, x2 = %lf\n", result->x1, result->x2);
        break;

    case INF_SOLUTIONS:
        printf("Решением является любое число\n");
        break;

    case NO_SOLUTIONS:
        printf("Нет решений\n");
        break;
    }

    DEF_COL
    return;
}

// Сравнивает два числа double и выводит 1 если они равны, 0 если различны
int Equal(double a, double b)
{
    return (fabs(a - b) < EPS);
}

// решает уравнения по коэффициентам из уравнений
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
        {
            return 0;
            break;
        }
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

// проверяет верны ли корни
bool CheckRoots(Coefficient *coef, Roots *roots)
{
    switch (roots->count_roots)
    {
        case TWO_SOLUTIONS:
        {
            double y1 = FindFuncValue(coef, roots->x1);
            double y2 = FindFuncValue(coef, roots->x2);

            if (Equal(y1, 0) && Equal(y2, 0))
                return 0;
            else
                return 1;
        }

        case ONE_SOLUTION:
        {
            double y1 = FindFuncValue(coef, roots->x1);

            if (Equal(y1, 0))
                return 0;
            else
                return 1;
        }

        case INF_SOLUTIONS:
        {
            if (roots->count_roots == INF_SOLUTIONS)
                return 0;
            else
                return 1;
        }

        case NO_SOLUTIONS:
        {
            if (roots->count_roots == NO_SOLUTIONS)
                return 0;
            else
                return 1;
        }
    }
    return 1;
}

// вычисляет значение квадратного уравнения, принимает коэффициенты и значение x
double FindFuncValue(Coefficient *coef, double x)
{
    double value = NAN;
    value = coef->a * x * x + coef->b * x + coef->c;
    return value;
}

// находит корни многочлена 2 степени
int StandardSqEqSolve(Coefficient *coef, Roots *result)
{
    assert(coef);
    assert(result);

    if (Equal(coef->a, 0))
    {
        Output(DIVISION_BY_ZERO, result);
        return 1;
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

    result->x1 = ((-coef->b) + sqrt_disc) / (2 * coef->a TEST_ERROR);
    result->x2 = ((-coef->b) - sqrt_disc) / (2 * coef->a);

    if (Equal(result->x1, result->x2))
    {
        result->count_roots = 1; result->x2 = NAN;
        result->count_roots = ONE_SOLUTION;
    }
    return 0;
}
