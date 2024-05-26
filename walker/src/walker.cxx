#include <raylib-cpp.hpp>
#include <myraylib.hxx>

class app {
public:
    app() {}
    ~app() {}
    void update(raylib::Window& window, int screenWidth, int screenHeight) {}
    void draw(raylib::Window& window, int screenWidth, int screenHeight) {
        raylib::Color foreground(0, 68, 130);
        raylib::Color background = RAYWHITE;

        window.ClearBackground(background);

        foreground.DrawRectangle(screenWidth / 2 - 128, screenHeight / 2 - 128, 256, 256);
        background.DrawRectangle(screenWidth / 2 - 112, screenHeight / 2 - 112, 224, 224);
        foreground.DrawText("raylib", screenWidth / 2 - 44, screenHeight / 2 + 24, 50);
        foreground.DrawText("cpp", screenWidth / 2 - 74, screenHeight / 2 + 54, 50);

        DrawText("this is NOT a texture!", 350, 370, 10, GRAY);
    }
};

int main()
{
    myraylib<app>(800, 450, "raylib [shapes] example - raylib logo using shapes", 60);
    return 0;
}

