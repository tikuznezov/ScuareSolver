#include <stdio.h>
#include <math.h>

#include "user_massages.cpp"


int input_abc_coef (double result[]);
// получаем коэффициенты и проверяем внеслись ли значения в переменные

void print_arr_double(double result[], int len, char name);
// выводит массив double подряд

void print_sqeq_roots(double result[], int len, char name);
// выводит корни уравнения

int sq_eq_solve(double coef[], double result[]);
// решает уравнение получая массив с коэффициентами и массив для результата

int lin_eq_solve(double coef[], double result[]);
// решает уравнение

void not_correct_input(double *coef);
// Вывод ошибки и очистка ввода

int show_grath(double coef[], int len_x, int len_y);
// рисует график функции в терминале (пока не готова)

void output(int error, double[]);
// switch и вывод результата


enum TYPE_OF_ERROR
{
    no_error                = 0,
    division_by_zero        = 1,
    discriminant_lower_zero = 2,
    incorrect_input         = 3,
    x_is_any_number         = 4,
    theres_no_solves        = 5,
    lin_eq                  = 6,
    user_is_byaka           = 7
};
// для лучшей читаемости присваиваю значения enum


int main()
{
    int error = 0;
    double abc[3] = {0};
    double x1_x2[2] = {0};

    hello_sq();
    want_sq();
    int res = 0;
    res = take_massage();
    A: switch(res)
    {
        case 0: error = user_is_byaka;   break;

        case 2: res = please();          goto A;

        case 1:
            clear_term();
            error = input_abc_coef(abc); // input a,b,c - получаем массив аргументов

            // func (a, b, c, &x1, &x2) - при необходимости получаем данные из массива
            if (error == 0)
                error = sq_eq_solve(abc, x1_x2);
    }

    // show_grath(abc, 9, 5); // рисует график в терминале (по идее должна)

    output(error, x1_x2); // проверяем ошибки, если все нормально, выводим корни
}


void output(int error, double x1_x2[])
{
    RED
    switch (error)
    {  // output result - выводим результат в нужном виде (a, b , c, x1, x2)
        case 0: print_sqeq_roots(x1_x2, 2, 'x');                 break;
        case 1: printf("Деление на ноль\n");                     break;
        case 2: printf("Дискриминант меньше нуля\n");            break;
        case 3: printf("Некорректный ввод\n");                   break;
        case 4: printf("Икс - любое число\n");                   break;
        case 5: printf("Нет решений\n");                         break;
        case 6: printf("Singe root: %lg\nlin_eq\n", x1_x2[0]);   break;
        case 7: printf("Ты бяка (ошибка ввода).\n");             break;
    }
    return;
}


int input_abc_coef(double result[])
{
    GREEN
    char coef[4] = "abc";
    printf("Введите коэффициенты квадратного уравнения: \n");
    for (int i = 0; i < 3; i++)
    {
        printf("%c = ", coef[i]);
        while (scanf("%lf", &(result[i])) != 1)
            return incorrect_input;
            //not_correct_input(&(result[i]));
    }
    return 0;
}


void print_arr_double(double result[], int len, char name)
{
    for (int i = 0; i < len; i++)
    {
        printf("%c%d = %lf\n", name , i, result[i]);
    }
}


int sq_eq_solve(double coef[], double result[])
{
    enum {a, b, c};
    enum {x1, x2};

    // проверки
    if ((coef[a] == 0) && (coef[b] = 0)) return theres_no_solves;
    if ((coef[a] == 0) && (coef[b] = 0) && (coef[c] == 0)) return x_is_any_number;
    if (coef[a] == 0)
    {
        lin_eq_solve(coef, result);
        return lin_eq;
    }

    double discriminant = coef[b]*coef[b] - 4*coef[a]*coef[c];
    if (discriminant < 0) // проверка, что дискриминант положительный
    {
        // printf("Discriminant < 0, roots not defined\n");
        // result[x1] = result[x2] = NULL;
        return discriminant_lower_zero;
    }
    double sqrt_disc = sqrt(discriminant);

    result[x1] = ((-coef[b]) + sqrt_disc) / (2 * coef[a]);
    result[x2] = ((-coef[b]) - sqrt_disc) / (2 * coef[a]);

    return 0;
}


int lin_eq_solve(double coef[], double result[])
{
    enum {b = 1, c = 2};
    enum {x1, x2};

    if (coef[b] == 0) return division_by_zero;

    result[x1] = result[x2] = (-coef[c]) / coef[b];
    return 0;
}


void print_sqeq_roots(double result[], int len, char name)
{
    enum {x1, x2};

    if (result[x1] == result[x2])
    {
        printf("Единственный корень: %lf\n", result[x1]);
        return;
    }
    else
    {
        printf("Два корня: \n");
        print_arr_double(result, len, name);
    }

    return;
}


void uncorrect_input(double *coef)
{
    clear_term();
    printf("\nОшибка ввода. Введенные символы не являются числом \n");
    printf("или число больше допустимого значения.\n");
    printf("Введите коэффициент заново: ");
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
//     if (coef[a] == 0) return division_by_zero;
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
