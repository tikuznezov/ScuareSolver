#include <stdio.h>

#define RED printf("\n\x1b[31;47m");
#define YELLOW printf("\x1b[33m");
#define GREEN printf("\x1b[32m");
#define DEF_COL printf("\x1b[0m");


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
    int c = 0;
    while (((c = getchar()) != EOF) && (c != '\n'));
}

int take_massage()
{
    clear_term();

    char current = getchar();

    if (current == 'd' || current == 'D' || current == 'Y' || current == 'y')
    {
        char current = getchar();

        if (current == 'a' || current == 'A')
        {
            printf("Оу, вы из Англии!\n");
            return 1;
        }
        else if (current == 'e' || current == 'E')
        {
            char current = getchar();

            if (current == 's' || current == 'S')
                return 1;
        }
    }

    else if (current == 'N' || current == 'n')
    {
        char current = getchar();
        if (current == 'o' || current == 'O')
            return 2;
        else if (current == 'e' || current == 'E')
        {
            current = getchar();
            if (current == 't' || current == 'T')
                return 2;
        }
    }


    return 0;
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
        case 0: return 0; break;
        case 1: printf("Урааа)\n"); return 1; break;
        case 2: return 0; break;
        }
    }
    else if (temp == 1)
    {
        printf("Урааа)\n");
        return 1;
    }
    return 0;
}
