#include <raylib-cpp.hpp>
#include <app.hxx>

class walker {
public:
    walker() {}
    ~walker() {}
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

FuncMap apps = {
    {"walker", AppDef {0, "", 
        [](const std::vector<std::string>& args){
            myraylib<walker>(800, 450, "raylib [shapes] example - raylib logo using shapes", 60, 0);
        }},
    },
};

int main(int argc, char** argv)
{
    const auto& args = parse_cmd_line_args("Nature of code", argc, argv,apps);
    callFunctionByName(apps, args.first, args.second);
    return 0;
}

