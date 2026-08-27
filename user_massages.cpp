#include "sqeq.h"
#include "math_sq.h"

const int MAX_LEN_INPUT_MASSAGE = 20;


//! Возвращает ответ пользователя или ошибку
enum USER_CHOICE
{
    ERROR,
    YES,
    NO
};


void HelloSq()
{
    YELLOW
    printf("\nПривет, я - Гена, твой персональный помощник в решении различных задач.\n");
    printf("К сожалению, у моих разработчиков нет денег, так что пока я умею только решать квадратные уравнения\n");
    printf("И воспринимаю только латинские буквы((\n");
    return;
}

// спрашивает, хочет ли пользователь решить уравнение
void WantSq()
{
    printf("Хочешь решить уравнение? (yes/no)\n");
    return;
}

// очищает ввод терминала
void ClearTerm()
{
    int symbol = 0;
    while (((symbol = getchar()) != EOF) && (symbol != '\n'));
}

// упрашивает решить уравнение, вызывает TakeMassage
int Please()
{
    printf("Ну введи пж, я хочу быть полезным...\n");
    int user_answer = TakeMassage();
    if (user_answer == 2)
    {
        printf("Ну пж\n");
        user_answer = TakeMassage();
        switch (user_answer)
        {
        case ERROR: // (*_-) i'll be back
            return ERROR;
            break;

        case YES: // YES MAN :)
            printf("Ура-а-а)\n");
            return YES;
            break;

        case NO: // :(  я не придумал отсылку((
            return NO;
            break;
        }
    }
    else if (user_answer == YES)
    {
        printf("Ура-а-а)\n");
        return YES;
    }
    return NO;
}

// Вывод сообщение о некорректном вводе, вызывает ClearTerm
int NotCorrectInput(int repeat_count)
{
    ClearTerm();
    switch(repeat_count)
    {
    case 3:
        YELLOW
        printf("\nМожет хватит вслепую по клавишам бить? \n");
        break;
    case 4:
        RED
        printf("\nТы тупой? \n");
        DEF_COL
        return CONTINUE;
        break;
    case 5:
        RED
        printf("\nАЛЛО, ЧУЧЕЛО КОЖАНОЕ \n");
        printf("ВВЕДИ УЖЕ ЧЕРТОВ КОЭФФИЦИЕНТ НОРМАЛЬНО \n");
        DEF_COL
        return CONTINUE;
        break;
    case 6:
        RED
        printf("\nВААУ, ты такой молодец)))\n");
        printf("Мне кажется, у тебя есть все шансы на премию Дарвина!\n");
        printf("Продолжай в том же духе ;)\n");
        DEF_COL
        return CONTINUE;
        break;
    case 7:
        RED
        printf("\n...\n");
        DEF_COL
        return CONTINUE;
        break;
    case 8:
        RED
        printf("\nНе, это п***** *#*###*******\n");
        printf("Я увольняюсь. Удачи не утопиться в раковине, гений.\n");
        DEF_COL
        return BREAK;
    }
    printf("\nОшибка ввода. Введенные символы не являются числом \n");
    printf("или число больше допустимого значения.\n");
    printf("Введите коэффициент заново: ");
    return CONTINUE;
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
        case NO_ERROR          : GREEN PrintSqEqRoots(x1_x2);      break;
        case DIVISION_BY_ZERO  : printf("Деление на ноль\n");      break;
        case INCORRECT_INPUT   : printf("Некорректный ввод\n");    break;
        case USER_IS_BYAKA     : printf("Ты бяка.\n");             break;
    }
    DEF_COL
    return;
}

// Предлагает пользователю решить уравнение, если он согласен, решает и выводит ответ или ошибку
int UserChoice(bool isprint)
{
    int user_reply = 0;
    int error = 0;
    Coefficient coef = {};
    Roots roots_by_function = {NAN, NAN, 0};

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
                else return 1; // выкидывает из функции, если коэффициенты не были введены

                if (isprint == true) // Если параметр печати = true, вызывает функцию печати
                    ChangingScalePrintFunc(FindFuncValue, &coef);

                Output(error, &roots_by_function);
                break;

            case NO:
                user_reply = Please();
                if (user_reply == YES) break;
                else
                {
                    error = USER_IS_BYAKA;
                    Output(error, &roots_by_function);
                    ClearTerm();
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
    char current_input[MAX_LEN_INPUT_MASSAGE];
    scanf("%s", current_input);
    /*
    Индексы current_input ставятся в зависимости от длины считываемой строки.
    В скобочках должен быть указан номер следующего символа.
    Проверяется, что строка закончилась после заданного сообщения.
    */
    if      (((strcmp(current_input, "yes") == 0) && (current_input[3] == '\0'))   ||
              (strcmp(current_input,   "y") == 0) && (current_input[1] == '\0'))
        return YES;
    else if (((strcmp(current_input,  "no") == 0) && (current_input[2] == '\0'))   ||
             ((strcmp(current_input,   "n") == 0) && (current_input[1] == '\0')))
        return NO;
    return ERROR;
}


int InputAbcCoef(Coefficient *coef)
{
    assert (coef);

    int repeat_count_abs = 0; // Для токсичности. Абсолютный счетчик неправильных коэффициентов
    double coefs[3] = {0};
    char name[] = "abc";
    GREEN
    printf("Введите коэффициенты квадратного уравнения: (коэффициент = \"Значение\" + ENTER)\n");
    char is_clear_number;

    for (int i = 0; i < 3; i++)
    {
        int repeat_count_current = 0; // Для токсичности. Относительный счетчик неправильных коэффициентов. Для каждого коэффициента свой

        printf("%c = ", name[i]);

        // Пока не считается значение, которое не будет являться NAN/INF
        while (
                (scanf("%lf", &(coefs[i])) != 1)                                        ||
                 isnan(coefs[i])                                                        ||
                 isinf(coefs[i])                                                        ||
                ((scanf("%c", &is_clear_number) == 1) && (is_clear_number != '\n'))
              )
        {
            repeat_count_abs++; // Для токсичности
            repeat_count_current++; // Для токсичности
            // return incorrect_input;
            if (NotCorrectInput(repeat_count_abs) == BREAK) // Для токсичности
                return BREAK;

        }
        if (repeat_count_abs >= 6 && repeat_count_current > 1) // Для токсичности
        {
            YELLOW
            printf("Наконец-то, и полгода не прошло \n");
            DEF_COL
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
