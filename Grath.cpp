#include "sqeq.h"

int ToOdd(int x) {
    if (x%2 == 0)
        return x+1;
    else
        return x;
}

int PrintFunc(double Func(Coefficient *, double), Coefficient *coef) {


    struct winsize window;
    ioctl(0, TIOCGWINSZ, &window);
    // ioctl - системный вызов
    // TIOCGWINSZ - код получения данных о размере окна

    // разрешение печати функции
    double resolution = window.ws_row * 2;

    // описание графика
    BLACKonWHITE
    printf("График функции (%lg)*x^2 + (%lg)*x + (%lg)\n", coef->a, coef->b, coef->c);
    DEF_COL

    // получение и стандартизация размеров поля
    int lenx = window.ws_col;
    lenx = ToOdd(lenx);
    int leny = window.ws_row * 2;
    leny = ToOdd(leny);

    int ox = (lenx - 1) / 2;
    int oy = (leny - 1) / 2;

    // инициализация экрана пробелами
    int count_of_points = lenx*leny;
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
    for (int x = (-ox * resolution); x <= (ox * resolution); x++) {
        double xreal = x/resolution;
        double y_coord = Func(coef, xreal) + oy;
        if ((0 < y_coord) && (y_coord < leny)) {
            int x_coord = xreal + ox;
            point[(int) y_coord][(int) x_coord] = 'x';
        }
    }


    BLACKonWHITE
    // выводим содержимое экрана
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
