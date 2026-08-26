#include "sqeq.h"
#include "math_sq.h"

struct Scale
{
    double x_factor;
    double y_factor;
};


int InitScreenSpaces(char **, const int, const int); // инициализация экрана пробелами

int InitAxesXY(char **, const int, const int, const int, const int); // рисует по центру координатные оси

int PrintScreen(char **, const int, const int); // выводит содержимое двумерного массива char в формате экрана

winsize ScreenSize(); // выдает структуру с размером экрана

Scale ScaleGrath(Coefficient *coef, winsize *window);




int PrintFunc(double Func(Coefficient *, double), Coefficient *coef) {

    winsize window = ScreenSize(); // структура с размером терминала

    double RESOLUTION = window.ws_row * 2; // количество проверяемых значений на один шаг по x

    const int PRINTED_SCREEN_COUNT = 2; // количество экранов по вертикали, которое будет занимать график

    Scale scale = ScaleGrath(coef, &window);

    // описание графика
    BLACKonWHITE
    printf("График функции (%lg)*x^2 + (%lg)*x + (%lg)  ", coef->a, coef->b, coef->c);
    printf("y_scale = %lg:1, x_factor = %lg:1\n", scale.y_factor, scale.x_factor);
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
        double x_real = x/RESOLUTION * scale.x_factor;
        double y_real = Func(coef, x_real);
        double y_coord = y_real / scale.y_factor + oy;
        if ((0 < y_coord) && (y_coord < leny))
        {
            int x_coord = x_real / scale.x_factor + ox;
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



int InitScreenSpaces(char **point, int lenx, int leny)
{
    assert(point);

    // инициализация экрана пробелами
    for (int y = 0; y < leny-1; y++)
        for (int x = 0; x < lenx-1; x++)
            point[y][x] = ' ';
    return 0;
}


int InitAxesXY(char **point, const int lenx, const int leny, const int ox, const int oy)
{
    for (int x = 0; x < lenx; x++)
        point[oy][x] = '-';
    for (int y = 0; y < leny; y++)
        point[y][ox] = '|';
    return 0;
}

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

winsize ScreenSize()
{
    struct winsize window;
    ioctl(0, TIOCGWINSZ, &window);
    // ioctl - системный вызов
    // TIOCGWINSZ - код получения данных о размере окна
    return window;
}

Scale ScaleGrath(Coefficient *coef, winsize *window)
{
    Scale scale = {.x_factor = 1, .y_factor = 1};

    if (Equal(coef->a, 0))
    {
        double root = (- coef->c) / coef->b;
        if ((abs(root) * 4) > window->ws_col) // если корень дальше четверти экрана от центра
            scale.x_factor = (window->ws_col)/(root); // масштабируем график

        if ((fabs(coef->c) * 4 > window->ws_row)) // если пересечение с Oy дальше четверти экрана от центра
            scale.y_factor = window->ws_row/coef->c; // масштабируем Oy
    }

    else
    {
        Point ext = {};
        Point zero = {.x = 0, .y = 0};
        ext.x = -coef->b / (2 * coef->a);
        ext.y = (coef->a * ext.x*ext.x) + (coef->b * ext.x) + coef->c;
        double dist = Distance(ext, zero);

        if ((dist * 2 > window->ws_row) or (dist * 2 > window->ws_col))
        {
            scale.y_factor = 4 * fabs(ext.y) / window->ws_row;
            scale.x_factor = 8 * fabs(ext.x) / window->ws_col;
        }
    }

    return scale;
}
