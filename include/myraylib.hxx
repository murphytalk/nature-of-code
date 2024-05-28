#pragma once
#include <raylib.h>
#include <Color.hpp>
#include <Window.hpp>
#include <memory>

template <class App, typename... Args>
void myraylib(int width, int height, const char* title, const int fps, unsigned int flags,
    // App constructor parameters
    Args &&... args
) {
/* On Linux if we do not hide window first and then clear the hidden flag after initialization the window won't display.
 * Possible reasons: 
 *  - Initialization Timing
 *  - Compositor Interaction
 *  - GLFW Behavior
 */
#ifdef __linux__
    flags |= FLAG_WINDOW_HIDDEN;
#endif
    raylib::Window window(width, height, title,flags);
#ifdef __linux__
    ClearWindowState(FLAG_WINDOW_HIDDEN);
#endif
    auto app = std::make_unique<App>(std::forward<Args>(args)...);

    SetTargetFPS(fps);
    while (!window.ShouldClose()) {    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Update your variables here
        //----------------------------------------------------------------------------------
        app->update(window, width, height);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        app->draw(window, width, height);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}

