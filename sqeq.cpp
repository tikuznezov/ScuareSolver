#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "user_massages.cpp"

// TODO: comments
// TODO: assert

// получаем коэффициенты и проверяем внеслись ли значения в переменные
int input_abc_coef(struct coefficient *coef);

// выводит корни уравнения
void print_sqeq_roots(struct roots *result);

// решает уравнение получая массив с коэффициентами и массив для результата
int sq_eq_solve(struct coefficient *coef, struct roots *x1_x2);

// решает уравнение
int lin_eq_solve(struct coefficient *coef, struct roots *x1_x2);

// Вывод ошибки и очистка ввода
void not_correct_input();

// рисует график функции в терминале (пока не готова)
int show_grath(struct coefficient coef, int len_x, int len_y);

// switch и вывод результата
void output(int error, struct roots *x1_x2);


// для лучшей читаемости присваиваю значения enum
enum TYPE_OF_ERROR
{
    NO_ERROR                = 0,
    DIVISION_BY_ZERO        = 1,
    DISCRIMINANT_LOWER_ZERO = 2,
    INCORRECT_INPUT         = 3,
    X_IS_ANY_NUMBER         = 4,
    THERES_NO_SOLVES        = 5,
    LIN_EQ                  = 6,
    USER_IS_BYAKA           = 7
};

struct roots
{
    double x1 = 0.f;
    double x2 = 0.f;
};

struct coefficient
{
    double a = 0.f;
    double b = 0.f;
    double c = 0.f;
};

int main()
{
    int error = 0;
    struct coefficient coef;
    struct roots x1_x2;



    hello_sq();

    int res = 0;
    // TODO: struct
    // TODO: goto -> while (do while)
    do
    {
        want_sq();
        res = take_massage();
        switch(res)
        {
            case YES:
                error = 0;
                error = input_abc_coef(&coef); // input a,b,c - получаем массив аргументов
                if (error == 0) error = sq_eq_solve(&coef, &x1_x2);
                output(error, &x1_x2);
                break;
            case NO:
                res = please();
                if (res == YES) break;
                else
                {
                    error = USER_IS_BYAKA;
                    output(error, &x1_x2);
                    break;
                }
            case ERROR:
                error = INCORRECT_INPUT;
                output(error, &x1_x2);
                return 0;
        }
    } while (res == YES);





//     switch(res)
//     {
//         case ERROR: error = USER_IS_BYAKA;   break;
//         case NO: res = please();             break; // начинает упрашивать и кидает на начало свитча
//         case YES:
//             clear_term();
//             error = input_abc_coef(&coef); // input a,b,c - получаем массив аргументов
//
//             if (error == 0)
//                 error = sq_eq_solve(&coef, &x1_x2);
//     }

    // show_grath(abc, 9, 5); // рисует график в терминале (по идее должна)

    // output(error, &x1_x2); // проверяем ошибки, если все нормально, выводим корни
}


void output(int error, struct roots *x1_x2)
{
    assert (x1_x2);
    RED
    switch(error)
    {  // output result - выводим результат в нужном виде (a, b , c, x1, x2)
        case NO_ERROR                : GREEN print_sqeq_roots(x1_x2);                  DEF_COL break;
        case DIVISION_BY_ZERO        : printf("Деление на ноль\n");                    DEF_COL break;
        case DISCRIMINANT_LOWER_ZERO : printf("Дискриминант меньше нуля\n");           DEF_COL break;
        case INCORRECT_INPUT         : printf("Некорректный ввод\n");                  DEF_COL break;
        case X_IS_ANY_NUMBER         : printf("Икс - любое число\n");                  DEF_COL break;
        case THERES_NO_SOLVES        : printf("Нет решений\n");                        DEF_COL break;
        case LIN_EQ                  : printf("Singe root: %lg\nlin_eq\n", x1_x2->x1); DEF_COL break;
        case USER_IS_BYAKA           : printf("Ты бяка.\n");                           DEF_COL break;
    }
    DEF_COL
    return;
}


int sq_eq_solve(struct coefficient *coef, struct roots *result)
{
    assert (coef);
    assert (result);

    // проверки
    if ((coef->a == 0) && (coef->b = 0) && (coef->c == 0)) return X_IS_ANY_NUMBER;
    else if ((coef->a == 0) && (coef->b = 0)) return THERES_NO_SOLVES;
    else if (coef->a == 0)
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
    if (result->x1 == result->x2)
    {
        printf("Единственный корень: %lf\n", result->x1);
        return;
    }
    else
    {
        printf("Два корня: x1 = %lg, x2 = %lg\n", result->x1, result->x2);
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
    for (int i = 0; i < 3; i++)
    {
        printf("%c = ", name[i]);
        while (scanf("%lf", &(coefs[i])) != 1)
            // return incorrect_input;
            not_correct_input();
    }
    coef->a = coefs[0];
    coef->b = coefs[1];
    coef->c = coefs[2];
    return 0;
    DEF_COL
}

// int show_grath(double coef[], int len_x, int len_y)
// {
//     enum {a, b, c};
//     int screen[len_x][len_y];
//     for (int i = 0; i < len_x; i++)
//     {
//         for (int j = 0; j < len_y; j++)
//         {
//             screen[i][j] = (i+j*10);
//         }
//     }
//     printf("\ninitialisation competed\n");
//
//     // разворот принта, если коэф а отрицательный
//     if (coef[a] >= 0)
//     {
//         #define REVERSE len_y - 1 -
//     }
//
//
//     for (int y = 0; y < len_y; y++)
//         {
//         for (int x = 0; x < len_x; x++)
//             printf("%2d ", screen[x][REVERSE y]);
//         printf("\n");
//         }
//
//     if (coef[a] == 0) return DIVISION_BY_ZERO;
//
//
//     double x_extr = (-coef[b]) / (2*coef[a]);
//     double y_extr = coef[a]*x_extr*x_extr + coef[b]*x_extr + c;
//
//
//     int middle = (int) len_x / 2;
//     printf("\nmiddle = %d\n", middle);
//
//     screen[0][0] = '0';
//     screen[middle][0] = 'c';
//
//     screen[len_x-1][len_y-1] = 'e';
//
//
//
//     return 0;
// }
