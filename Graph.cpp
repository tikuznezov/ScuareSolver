#include "../Headers/sqeq.h"
#include "../Headers/math_sq.h"


int InitScreenSpaces(char **, const int, const int); // инициализация экрана пробелами

int InitAxesXY(char **, const int, const int, const int, const int); // рисует по центру координатные оси

int PrintScreen(char **, const int, const int); // выводит содержимое двумерного массива char в формате экрана

winsize ScreenSize(); // выдает структуру с размером экрана

Scale ScaleGraph(Coefficient *coef, winsize *window);




int PrintFunc(double Func(Coefficient *, double), Coefficient *coef, Scale *user_scale_coef)
{
    assert(Func);
    assert(coef);
    assert(user_scale_coef);

    winsize window = ScreenSize(); // структура с размером терминала

    double RESOLUTION = window.ws_row * 2; // количество проверяемых значений на один шаг по x

    const float PRINTED_SCREEN_COUNT = 1.5; // количество экранов по вертикали, которое будет занимать график


    Scale scale = ScaleGraph(coef, &window); // структура, содержащая автоматический масштаб
    // учет пользовательского масштаба
    double scale_x = scale.x_factor * user_scale_coef->x_factor;
    double scale_y = scale.y_factor * user_scale_coef->y_factor;


    // описание графика
    BLACKonWHITE
    printf("График функции (%lg)*x^2 + (%lg)*x + (%lg)  \n", coef->a, coef->b, coef->c);
    PRED
    printf("y scale = %lg:1, x scale = %lg:1\n", scale.y_factor, scale.x_factor);
    DEF_COL


    // получение и стандартизация размеров поля
    const int lenx = ToOdd(window.ws_col);
    const int leny = ToOdd(window.ws_row * PRINTED_SCREEN_COUNT);

    const int ox = (lenx - 1) / 2;
    const int oy = (leny - 1) / 2;

    // создание экрана
    // char **point = (char**) calloc(leny*lenx, sizeof(char));
    char point[leny][lenx];


    // InitScreenSpaces(point, lenx, leny); // инициализация экрана пробелами
    // инициализация экрана пробелами
    for (int y = 0; y < leny; y++)
        for (int x = 0; x < lenx; x++)
            point[y][x] = ' ';

    // рисует координатные оси
    // InitAxesXY(point, lenx, leny, ox, oy);
    // printf("Оси\n");
    for (int x = 0; x < lenx; x++)
        point[oy][x] = '-';
    for (int y = 0; y < leny; y++)
        point[y][ox] = '|';

    // printf("Отмечаем точки\n");
    // отмечает точки удовлетворяющие функции
    for (int x = (-ox * RESOLUTION); x <= (ox * RESOLUTION); x+=1)
    {
        double x_real = x/RESOLUTION * scale_x;
        double y_real = Func(coef, x_real);

            double y_coord = y_real / scale_y + oy;
            if ((0 < y_coord) && (y_coord < leny))
            {
            double x_coord = x_real / scale_x + ox;
                point[(int) y_coord][(int) x_coord] = 'x';
            }
    }

    // PrintScreen(point, lenx, leny); // выводит содержимое экрана
    // printf("Печать графика\n");
    BLACKonWHITE
    for (int y = leny-1; y >= 0; y--)
    {
        for (int x = 0; x < lenx; x++)
            printf("%c", point[y][x]);
        printf("\n");
    }
    DEF_COL
    printf("\n");
    return 0;
}

// инициализация экрана пробелами
int InitScreenSpaces(char **point, int lenx, int leny)
{
    assert(point);

    for (int y = 0; y < leny-1; y++)
        for (int x = 0; x < lenx-1; x++)
            point[y][x] = ' ';
    return 0;
}

// создание осей x, y
int InitAxesXY(char **point, const int lenx, const int leny, const int ox, const int oy)
{
    for (int x = 0; x < lenx; x++)
        point[oy][x] = '-';
    for (int y = 0; y < leny; y++)
        point[y][ox] = '|';
    return 0;
}

// вывод содержимого двумерного массива в виде экрана
int PrintScreen(char **point, int lenx, int leny) // выводит содержимое экрана
{
    BLACKonWHITE
    for (int y = leny-1; y >= 0; y--)
    {
        for (int x = 0; x < lenx; x++)
            printf("%c", point[y][x]);
        printf("\n");
    }
    DEF_COL
    printf("\n");
    return 0;
}

// Системный вызов -> получение размеров окна терминала
winsize ScreenSize()
{
    struct winsize window;
    ioctl(0, TIOCGWINSZ, &window);
    // ioctl - системный вызов
    // TIOCGWINSZ - код получения данных о размере окна
    return window;
}

/**
 * @brief Функция получает на вход размеры окна и коэффициенты уравнения не старше второй степени
 *        и изменяет масштаб таким образом, чтобы пересечения с осями (или вершина параболы)
 *        находились не далее от перпендикулярной оси, чем константы dist_x и dist_y, поделенные на два
 *
 *
 * @param coef
 * @param window
 * @return Scale
 */
Scale ScaleGraph(Coefficient *coef, winsize *window)
{
    const int dist_x = 8; //
    const int dist_y = 8;


    Scale scale = {.x_factor = 1, .y_factor = 1};


    if (Equal(coef->a, 0))
    {
        if (!Equal(coef->b, 0))
        {
            double root = (- coef->c) / coef->b;
            if ((abs(root) > window->ws_col)) // если корень дальше четверти экрана от центра
                scale.x_factor = root/window->ws_col / pow(fabs(coef->a), 0.5/log(fabs(coef->a))); // масштабируем график
        }

        if ((fabs(coef->c) > window->ws_row)) // если пересечение с Oy дальше четверти экрана от центра
            scale.y_factor = 4 * coef->c/window->ws_row; // масштабируем Oy
    }

    else
    {
        Point ext = {};
        ext.x = -coef->b / (2 * coef->a);
        ext.y = (coef->a * ext.x*ext.x) + (coef->b * ext.x) + coef->c;


        // if ((dist * 2 > window->ws_row) || (dist * 2 > window->ws_col))
        // {
        // if (Equal(ext.y, 0) == false)
            scale.y_factor = dist_x * fabs(ext.y+0.1) / window->ws_row / pow(fabs(coef->a), 0.5/log(fabs(coef->a))); // n отвечает за дальность отступа по координате от центра координат. 4 - не дальше 1/4 экрана, то есть не дальше половины координатной полуплоскости
        // if (Equal(ext.x, 0) == false)
            scale.x_factor = dist_y * fabs(ext.x+0.1) / window->ws_col / pow(fabs(coef->a), 1/log(fabs(coef->a))) * sqrt(abs(coef->c));
        // }
    }

    return scale;
}

// привести в адекватный вид
void ChangingScalePrintFunc(double Func(Coefficient *, double), Coefficient *coef)
{
    Scale user_scale = {.x_factor = 1, .y_factor = 1};
    PrintFunc(Func, coef, &user_scale);
    double user_scale_coef_x = 1;
    double user_scale_coef_y = 1;

    char reply = NULL;
    printf("Хотите изменить масштаб? (y/n)\n");

    char next_symbol = '\n';
    scanf("%c%c", &reply, &next_symbol);
    if (next_symbol != '\n')
    {
        ClearTerm();
        return; // я сделаю тут нормальный сценарий, а не return
    }

    while (reply == 'y')
    {
        printf("Введите коэффициент изменения масштаба для осей, которые хотите изменить: \"x-scale, y-scale\" \n");
        scanf("%lf, %lf", &user_scale_coef_x, &user_scale_coef_y);

        user_scale.x_factor *= user_scale_coef_x;
        user_scale.y_factor *= user_scale_coef_y;

        PrintFunc(Func, coef, &user_scale);

        printf("Хотите изменить масштаб? (y/n)\n");
        char next_symbol = '\n';
        ClearTerm();
        scanf("%c", &reply);
    }
}
