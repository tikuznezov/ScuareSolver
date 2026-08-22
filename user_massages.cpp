#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

enum USER_CHOICE
{
    ERROR,
    YES,
    NO
};



int HelloSq()
{
    YELLOW
    printf("Привет, я - Гена, твой персональный помощник в решении различных задач.\n");
    printf("К сожалению, у моих разработчиков нет денег, так что пока я умею только решать квадратные уравнения\n");
    printf("И воспринимаю только латинские буквы((\n");
    return 0;
}


int WantSq()
{
    printf("Хочешь решить уравнение? (Yes/No)\n");
    return 0;
}


void ClearTerm()
{
    int symbol = 0;
    while (((symbol = getchar()) != EOF) && (symbol != '\n'));
}


int TakeMassage()
{

    char current = getchar();

    char current_input[10] = {};


    scanf("%s", current_input);

    // strcmp(current_input, "yes");

    if (current == 'd' || current == 'D' || current == 'Y' || current == 'y')
    {
        SKIP_YES

        char current = getchar();
        if (current == 'a' || current == 'A')
        {
            printf("Оу, вы из Англии!\n");
            return YES;
        }
        else if (current == 'e' || current == 'E')
        {
            char current = getchar();
            if (current == 's' || current == 'S')
                return YES;
        }
    }

    else if (current == 'N' || current == 'n')
    {
        SKIP_NO

        char current = getchar();
        if (current == 'o' || current == 'O')
            return NO;
        else if (current == 'e' || current == 'E')
        {
            current = getchar();
            if (current == 't' || current == 'T')
                return NO;
        }
    }
    return ERROR;
}


int Please()
{
    printf("Ну введи пж, я хочу быть полезным...\n");
    int temp = TakeMassage();
    if (temp == 2)
    {
        printf("Ну пж\n");
        int temp = TakeMassage();
        switch (temp)
        {
        case ERROR: return 0; break;
        case YES: printf("Урааа)\n"); return 1; break;
        case NO: return 0; break;
        }
    }
    else if (temp == 1)
    {
        printf("Урааа)\n");
        return 1;
    }
    return 0;
}


void NotCorrectInput()
{
    ClearTerm();
    printf("\nОшибка ввода. Введенные символы не являются числом \n");
    printf("или число больше допустимого значения.\n");
    printf("Введите коэффициент заново: ");
}

int WantAnotherOne()
{
    GREEN
    printf("Хочешь продолжить?\n");
    return TakeMassage();
}

void Output(int error, struct Roots *x1_x2)
{
    assert (x1_x2);
    RED
    switch(error)
    {  // Output result - выводим результат в нужном виде (a, b , c, x1, x2)
        case NO_ERROR                : GREEN PrintSqEqRoots(x1_x2);                                 break;
        case DIVISION_BY_ZERO        : printf("Деление на ноль\n");                                 break;
        case INCORRECT_INPUT         : printf("Некорректный ввод\n");                               break;
        case USER_IS_BYAKA           : printf("Ты бяка.\n");                                        break;
    }
    DEF_COL
    return;
}


int UserChoice()
{
    int user_reply = 0;
    int error = 0;
    struct Coefficient coef;
    struct Roots roots_by_function;
    do
    {
        WantSq();
        user_reply = TakeMassage();
        ClearTerm();
        switch(user_reply)
        {
            case YES:
                error = 0;
                error = InputAbcCoef(&coef); // input a,b,c - получаем массив аргументов
                if (error == 0) error = SqEqSolve(&coef, &roots_by_function);
                Output(error, &roots_by_function);
                break;
            case NO:
                user_reply = Please();
                if (user_reply == YES) break;
                else
                {
                    error = USER_IS_BYAKA;
                    Output(error, &roots_by_function);
                    break;
                }
            case ERROR:
                error = INCORRECT_INPUT;
                Output(error, &roots_by_function);
                return 0;
        }
    } while (user_reply == YES);
    return 0;
}
