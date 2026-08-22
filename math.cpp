#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

// погрешность приравнивания к нулю
const double EPS = (0.000000000000000001);

int sq_eq_solve(struct coefficient *coef, struct roots *result)
{
    assert (coef);
    assert (result);

    // проверки
    if (equal(coef->a, 0) && equal(coef->b, 0) && equal(coef->c, 0)) return X_IS_ANY_NUMBER;
    else if (equal(coef->a, 0) && equal(coef->b, 0)) return THERES_NO_SOLVES;
    else if (equal(coef->a, 0))
    {
        lin_eq_solve(coef, result);
        return LIN_EQ;
    }

    double discriminant = (coef->b * coef->b) - (4 * coef->a * coef->c);
    if (discriminant < 0) // проверка, что дискриминант положительный
    {
        // printf("Discriminant < 0, roots not defined\n");
        // result[x1] = result[x2] = NULL;
        return DISCRIMINANT_LOWER_ZERO;
    }
    double sqrt_disc = sqrt(discriminant);

    result->x1 = ((-coef->b) + sqrt_disc) / (2 * coef->a);
    result->x2 = ((-coef->b) - sqrt_disc) / (2 * coef->a);

    return 0;
}


int lin_eq_solve(struct coefficient *coef, struct roots *result)
{
    assert (result);
    assert (coef);
    if (coef->b == 0) return DIVISION_BY_ZERO;

    result->x1 = result->x2 = (- coef->c) / coef->b;
    return 0;
}


void print_sqeq_roots(struct roots *result)
{
    assert (result);
    GREEN
    if (result->x1 == result->x2)//(equal(result->x1, result->x2, EPS))
    {
        printf("Единственный корень: %lf\n", result->x1);
        return;
    }
    else
    {
        printf("Два корня: x1 = %lf, x2 = %lf\n", result->x1, result->x2);
    }
    return;
    DEF_COL
}


int input_abc_coef(struct coefficient *coef)
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
            not_correct_input();
        }
    }
    coef->a = coefs[0];
    coef->b = coefs[1];
    coef->c = coefs[2];
    return 0;
    DEF_COL
}

int equal(double a, double b)
{
    if (fabs(a - b) < EPS) return 1;
    else return 0;
}
