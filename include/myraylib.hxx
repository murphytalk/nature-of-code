#pragma once
#include <raylib.h>
#include <Color.hpp>
#include <Window.hpp>
#include <functional>

using DrawFunc = std::function<void(raylib::Window&, int, int)>;
class myraylib_t {
public:
    myraylib_t(int width, int height, const char* title, const int fps, DrawFunc& draw_func) {

        raylib::Window window(width, height, title);

        SetTargetFPS(fps);

        while (!window.ShouldClose()) {    // Detect window close button or ESC key
            // Update
            //----------------------------------------------------------------------------------
            // Update your variables here
            //----------------------------------------------------------------------------------

            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            draw_func(window, width, height);
            EndDrawing();
            //----------------------------------------------------------------------------------
        }
    }
};