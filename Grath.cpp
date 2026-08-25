#include "sqeq.h"

int PrintFunc(double Func(Coefficient *, double), Coefficient *coef) {


    struct winsize window;
    ioctl(0, TIOCGWINSZ, &window);
    // ioctl - системный вызов
    // TIOCGWINSZ - код получения данных о размере окна


    const double RESOLUTION = window.ws_row * 2; // разрешение печати функции

    const int PRINTED_SCREEN_COUNT = 2; // количество экранов по вертикали, которое будет занимать график

    // описание графика
    BLACKonWHITE
    printf("График функции (%lg)*x^2 + (%lg)*x + (%lg)\n", coef->a, coef->b, coef->c);
    DEF_COL

    // получение и стандартизация размеров поля
    const int lenx = ToOdd(window.ws_col);
    const int leny = ToOdd(window.ws_row * PRINTED_SCREEN_COUNT);

    const int ox = (lenx - 1) / 2;
    const int oy = (leny - 1) / 2;

    // инициализация экрана пробелами
    char point[leny][lenx];
    for (int y = 0; y < leny; y++)
        for (int x = 0; x < lenx; x++)
            point[y][x] = ' ';

    // рисуем оси
    for (int x = 0; x < lenx; x++)
        point[oy][x] = '-';
    for (int y = 0; y < leny; y++)
        point[y][ox] = '|';


    // отмечает точки удовлетворяющие функции
    for (int x = (-ox * RESOLUTION); x <= (ox * RESOLUTION); x++)
    {
        double x_real = x/RESOLUTION;
        double y_coord = Func(coef, x_real) + oy;
        if ((0 < y_coord) && (y_coord < leny))
        {
            int x_coord = x_real + ox;
            point[(int) y_coord][(int) x_coord] = 'x';
        }
    }


    // выводим содержимое экрана
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
