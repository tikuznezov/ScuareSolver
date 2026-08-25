#include "sqeq.h"

const int MAX_LEN_INPUT_MASSAGE = 20;
const int HOW_MANY_SYMBOLS_READ = 1;

enum USER_CHOICE
{
    ERROR,
    YES,
    NO
};


int HelloSq()
{
    YELLOW
    printf("\nПривет, я - Гена, твой персональный помощник в решении различных задач.\n");
    printf("К сожалению, у моих разработчиков нет денег, так что пока я умею только решать квадратные уравнения\n");
    printf("И воспринимаю только латинские буквы((\n");
    return 0;
}

// спрашивает, хочет ли пользователь решить уравнение
int WantSq()
{
    printf("Хочешь решить уравнение? (yes/no)\n");
    return 0;
}

// очищает ввод терминала
void ClearTerm()
{
    int symbol = 0;
    while (((symbol = getchar()) != EOF) && (symbol != '\n'));
}

// // считывает ввод и возвращает YES NO ERROR
// int TakeMassage_1() // прошлая версия
// {
//
//     char current = getchar();
//
//     char current_input[10] = {};
//
//
//     scanf("%s", current_input);
//
//     // strcmp(current_input, "yes");
//
//     if (current == 'd' || current == 'D' || current == 'Y' || current == 'y')
//     {
//         SKIP_YES
//
//         char current = getchar();
//         if (current == 'a' || current == 'A')
//         {
//             printf("Оу, вы из Англии!\n");
//             return YES;
//         }
//         else if (current == 'e' || current == 'E')
//         {
//             char current = getchar();
//             if (current == 's' || current == 'S')
//                 return YES;
//         }
//     }
//
//     else if (current == 'N' || current == 'n')
//     {
//         SKIP_NO
//
//         char current = getchar();
//         if (current == 'o' || current == 'O')
//             return NO;
//         else if (current == 'e' || current == 'E')
//         {
//             current = getchar();
//             if (current == 't' || current == 'T')
//                 return NO;
//         }
//     }
//     return ERROR;
// }

// упрашивает решить уравнение, вызывает TakeMassage
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

// Вывод сообщение о некорректном вводе, вызывает ClearTerm
void NotCorrectInput()
{
    ClearTerm();
    printf("\nОшибка ввода. Введенные символы не являются числом \n");
    printf("или число больше допустимого значения.\n");
    printf("Введите коэффициент заново: ");
}

// Спрашивает, хочет ли пользователь решить еще одно уравнение, вызывает TakeMassage
int WantAnotherOne()
{
    GREEN
    printf("Хочешь продолжить?\n");
    return TakeMassage();
}

// Считывает ошибки, если их нет, вызывает PrintSqEqRoots, иначе выводит сообщение о ошибке
void Output(int error, Roots *x1_x2)
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

// Предлагает пользователю решить уравнение, если он согласен, решает и выводит ответ или ошибку
int UserChoice(bool isprint)
{
    int user_reply = 0;
    int error = 0;
    Coefficient coef;
    Roots roots_by_function;

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
                if (isprint == true)
                    PrintFunc(FindFuncValue, &coef);
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

// считывает ввод и возвращает YES NO ERROR
int TakeMassage()
{
    char cerrent_input[MAX_LEN_INPUT_MASSAGE];
    scanf("%s", cerrent_input);
    if (strncmp(cerrent_input, "yes", HOW_MANY_SYMBOLS_READ) == 0)
        return YES;
    else if (strncmp(cerrent_input, "no", HOW_MANY_SYMBOLS_READ) == 0)
        return NO;
    return ERROR;
}


int InputAbcCoef(Coefficient *coef)
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
        while ((scanf("%lf", &(coefs[i])) != 1) || ((scanf("%c", &temp) == 1) && (temp != '\n')))
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


// выводит корни и количество решений
void PrintCoefs(Coefficient *coef)
{
    printf("a = %lf, b = %lf, c = %lf\n", coef->a, coef->b, coef->c);
}

//выводит корни и их количество
void PrintRoots(Roots *roots)
{
    printf("Count of roots: %d; Roots: x1 = %12.3lf, x2 = %12.3lf\n", roots->count_roots, roots->x1, roots->x2);
}

// Выводит, что может делать эта программа
void WhatCanDoThisProgram()
{
    GREEN
    printf("Вы запустили программу, которая предназначена для решения квадратных уравнений.\n\n");
    printf("Запустите программу заново и выберете действие: \n");

    printf("Ввести коэффициенты вручную - после имени программы введите \"run_AI\" (\"-r\") ->\n");
    printf("-> и \"-pr\", если хотите вывести в терминал график функции\n");
    printf("Ввести данные из файла - введите \"-f\" \"путь к файлу\" \n");
    printf("Запустить встроенные тесты перед началом работы - введите \"st\" \n");
    printf("Запустить тесты из файла - введите \"-ft\" \"путь к файлу\" \n");
    printf("Запустить тесты со случайными величинами - введите \"-RT!\" \"путь к файлу\" \n");

    printf("\nПараметры из разных строк можно комбинировать в произвольном порядке.\n\n");
    DEF_COL
}
