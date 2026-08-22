#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

#include "user_massages.cpp"
#include "math.cpp"


int main()
{
    int error = 0;
    struct coefficient coef;
    struct roots x1_x2;

    hello_sq();
    int res = 0;
    do
    {
        want_sq();
        res = take_massage();
        clear_term();
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
}
