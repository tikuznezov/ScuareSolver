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



int hello_sq()
{
    YELLOW
    printf("Привет, я - Гена, твой персональный помощник в решении различных задач.\n");
    printf("К сожалению, у моих разработчиков нет денег, так что пока я умею только решать квадратные уравнения\n");
    printf("И воспринимаю только латинские буквы((\n");
    return 0;
}


int want_sq()
{
    printf("Хочешь решить уравнение? (Yes/No)\n");
    return 0;
}


void clear_term()
{
    int symbol = 0;
    while (((symbol = getchar()) != EOF) && (symbol != '\n'));
}


int take_massage()
{
    clear_term();

    char current = getchar();

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


int please()
{
    printf("Ну введи пж, я хочу быть полезным...\n");
    int temp = take_massage();
    if (temp == 2)
    {
        printf("Ну пж\n");
        int temp = take_massage();
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


void not_correct_input()
{
    clear_term();
    printf("\nОшибка ввода. Введенные символы не являются числом \n");
    printf("или число больше допустимого значения.\n");
    printf("Введите коэффициент заново: ");
}

int want_another_one()
{
    GREEN
    printf("Хочешь продолжить?\n");
    return take_massage();
}

void output(int error, struct roots *x1_x2)
{
    assert (x1_x2);
    RED
    switch(error)
    {  // output result - выводим результат в нужном виде (a, b , c, x1, x2)
        case NO_ERROR                : GREEN print_sqeq_roots(x1_x2);                               break;
        case DIVISION_BY_ZERO        : printf("Деление на ноль\n");                                 break;
        case DISCRIMINANT_LOWER_ZERO : printf("Дискриминант меньше нуля\n");                        break;
        case INCORRECT_INPUT         : printf("Некорректный ввод\n");                               break;
        case X_IS_ANY_NUMBER         : printf("Икс - любое число\n");                               break;
        case THERES_NO_SOLVES        : printf("Нет решений\n");                                     break;
        case LIN_EQ                  : printf("Singe root: %lg\nЛинейное уравнение\n", x1_x2->x1);  break;
        case USER_IS_BYAKA           : printf("Ты бяка.\n");                                        break;
    }
    DEF_COL
    return;
}
