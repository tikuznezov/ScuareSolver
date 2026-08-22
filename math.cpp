#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

// погрешность приравнивания к нулю
const double EPS = (0.000000000000000000001);

int SqEqSolve(struct Coefficient *coef, struct Roots *result)
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
            else
            {
            result->count_roots = NO_SOLUTIONS;
            return 0;
            }
        }

        else
        {
            LinEqSolve(coef, result);
            return 0;
        }
    }

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

    return 0;
}


int LinEqSolve(struct Coefficient *coef, struct Roots *result)
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


void PrintSqEqRoots(struct Roots *result)
{
// TODO switch
    assert (result);
    GREEN
    if (result->count_roots == ONE_SOLUTION)
    {
        printf("Единственный корень: %lf\n", result->x1);
        return;
    }
    else if (result->count_roots == TWO_SOLUTIONS)
    {
        printf("Два корня: x1 = %lf, x2 = %lf\n", result->x1, result->x2);
    }
    else if (result->count_roots == INF_SOLUTIONS)
    {
        printf("Решением является любое число\n");
    }
    else if (result->count_roots == NO_SOLUTIONS)
    {
        printf("Нет решений\n");
    }
    return;
    DEF_COL
}


int InputAbcCoef(struct Coefficient *coef)
{
    assert (coef);

    double coefs[3] = {0};
    char name[] = "abc";
    GREEN
    printf("Введите коэффициенты квадратного уравнения: \n");
    char temp;
    for (int i = 0; i < 3; i++)
    {
        printf("%c = ", name[i]);
        while ((scanf("%lf", &(coefs[i])) != 1) && (scanf("%c", &temp) == 1))
        {
            // return incorrect_input;
            NotCorrectInput();
        }
    }
    coef->a = coefs[0];
    coef->b = coefs[1];
    coef->c = coefs[2];
    return 0;
    DEF_COL
}

int Equal(double a, double b)
{
    if (fabs(a - b) < EPS) return 1;
    else return 0;
}
