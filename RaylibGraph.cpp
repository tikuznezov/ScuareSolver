#include <stdio.h>
#include "/opt/homebrew/include/raylib.h"
#include "../Headers/sqeq.h"
#include "../Headers/math_sq.h"

// -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit

Scale ScaleGraphRay(Coefficient *coef, winsize *window)
{
    const int dist_x = 4;
    const int dist_y = 8;


    Scale scale = {.x_factor = 1, .y_factor = 1};


    if (Equal(coef->a, 0))
    {
        if (!Equal(coef->b, 0))
        {
            double root = abs((- coef->c) / coef->b);
            scale.x_factor = pow(root, 1.2) / pow(coef->b, 0.02); // масштабируем график
        }

        if ((fabs(coef->c) > window->ws_row)) // если пересечение с Oy дальше четверти экрана от центра
            scale.y_factor = 4 * coef->c/window->ws_row; // масштабируем Oy
    }

    else
    {
        Point ext = {};
        ext.x = (-coef->b / (2 * coef->a)) + (window->ws_col / 2);
        ext.y = ((coef->a * ext.x*ext.x) + (coef->b * ext.x) + coef->c) + (window->ws_row / 2);


        scale.y_factor = dist_x * fabs(ext.y+0.1) / window->ws_row / pow(fabs(coef->a), 0.7/log(fabs(coef->a))); // n отвечает за дальность отступа по координате от центра координат. 4 - не дальше 1/4 экрана, то есть не дальше половины координатной полуплоскости
        scale.x_factor = dist_y * fabs(ext.x+0.1) / window->ws_col / pow(fabs(coef->a), 1/log(fabs(coef->a))) * pow(abs(coef->c), 1/log(fabs(coef->c))) * pow(abs(coef->b), 1/log(fabs(coef->b)));
    }

    return scale;
}


void PrintFuncRay(double Func(Coefficient *, double), Coefficient *coef)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int RESOLUTION = screenHeight/5;
    Scale scale = {.x_factor = 1, .y_factor = 1};

    winsize window = {.ws_col = screenWidth, .ws_row = screenHeight};

    scale = ScaleGraphRay(coef, &window);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    int ox = screenHeight/2;
    int oy = screenWidth/2;

    SetTargetFPS(1);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Scale user_scale = {.x_factor = 1, .y_factor = 1};
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        BeginDrawing();
        // if (IsKeyPressed('e'))
        //     scale.x_factor *= 1.2;
        // scale.y_factor *= user_scale.y_factor;

            ClearBackground(RAYWHITE);

            DrawLine(0, ox, screenWidth, ox, GRAY);
            DrawLine(oy, 0, oy, screenHeight, GRAY);

            int step_x = 100;
            int step_y = 100;
            char buffer[50]; // вроде как его можно не чистить. Строка перезаписывается и заканчивается \0, так что дальше читаться не будет

            // отрисовка разметки на оси x
            for (int x = oy; x < screenWidth; x+=step_x) // рисует штрихи через каждые step_x пикселей вдоль положительного направления ox
            {
                DrawLine(x, ox - screenHeight/100 , x, ox + screenHeight/100 , GRAY);
                snprintf(buffer, 40, "%.4f", ((double) x - oy)*scale.x_factor);
                DrawText(buffer, x - 10, ox + 10, 1, BLACK);
            }
            for (int x = oy-step_x; x > 0          ; x-=step_x) // рисует штрихи через каждые step_x пикселей вдоль отрицательного направления ox
            {
                DrawLine(x, ox - screenHeight/100 , x, ox + screenHeight/100 , GRAY);
                snprintf(buffer, 40, "%.4f", ((double) x - oy)*scale.x_factor);
                DrawText(buffer, x - 25, ox + 10, 1, BLACK);
            }

            // отрисовка разметки по оси y
            for (int y = ox + step_y; y < screenHeight; y+=step_y) // рисует штрихи через каждые step_y пикселей вдоль положительного направления oy
            {
                DrawLine(oy - screenWidth/100 , y, oy + screenWidth/100 , y, GRAY);
                snprintf(buffer, 40, "%.4f", ((double) -y + ox)*scale.y_factor);
                DrawText(buffer, oy + 10, y - 5, 1, BLACK);
            }
            for (int y = ox - step_y; y > 0           ; y-=step_y) // рисует штрихи через каждые step_y пикселей вдоль отрицательного направления oy
            {
                DrawLine(oy - screenWidth/100 , y, oy + screenWidth/100 , y, GRAY);
                snprintf(buffer, 40, "%.4f", ((double) -y + ox)*scale.y_factor);
                DrawText(buffer, oy + 10, y - 5, 1, BLACK);
            }



                    // отмечает точки удовлетворяющие функции
            for (float x = 0; x <= screenWidth * RESOLUTION; x++)
            {
                float x_real = (x / RESOLUTION - oy) * scale.x_factor;
                float y_real = Func(coef, x_real);

                    float y_coord = y_real / scale.y_factor;

                if ((-y_coord + ox) <= screenHeight)
                {
                    float x_coord = x_real / scale.x_factor;

                        DrawPixel((int) x_coord + oy, (int) - y_coord + ox, BLACK);
                }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    CloseWindow();
}


/*
// void DrawText(const char *text, int posX, int posY, int fontSize, Color color);


// Input-related functions: keyboard
    bool IsKeyPressed(int key);                             // Check if a key has been pressed once
    bool IsKeyPressedRepeat(int key);                       // Check if a key has been pressed again
    bool IsKeyDown(int key);                                // Check if a key is being pressed
    bool IsKeyReleased(int key);                            // Check if a key has been released once
    bool IsKeyUp(int key);                                  // Check if a key is NOT being pressed
    int GetKeyPressed(void);                                // Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
    int GetCharPressed(void);                               // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
    const char *GetKeyName(int key);                        // Get name of a QWERTY key on the current keyboard layout (eg returns string 'q' for KEY_A on an AZERTY keyboard)
    void SetExitKey(int key);                               // Set a custom key to exit program (default is ESC)


// Input-related functions: mouse
    bool IsMouseButtonPressed(int button);                  // Check if a mouse button has been pressed once
    bool IsMouseButtonDown(int button);                     // Check if a mouse button is being pressed
    bool IsMouseButtonReleased(int button);                 // Check if a mouse button has been released once
    bool IsMouseButtonUp(int button);                       // Check if a mouse button is NOT being pressed
    int GetMouseX(void);                                    // Get mouse position X
    int GetMouseY(void);                                    // Get mouse position Y
    Vector2 GetMousePosition(void);                         // Get mouse position XY
    Vector2 GetMouseDelta(void);                            // Get mouse delta between frames
    void SetMousePosition(int x, int y);                    // Set mouse position XY
    void SetMouseOffset(int offsetX, int offsetY);          // Set mouse offset
    void SetMouseScale(float scaleX, float scaleY);         // Set mouse scaling
    float GetMouseWheelMove(void);                          // Get mouse wheel movement for X or Y, whichever is larger
    Vector2 GetMouseWheelMoveV(void);                       // Get mouse wheel movement for both X and Y
    void SetMouseCursor(int cursor);                        // Set mouse cursor
*/
