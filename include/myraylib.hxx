#pragma once
#include <raylib.h>
#include <Color.hpp>
#include <Window.hpp>
#include <functional>
#include <memory>

template <class App, typename... Args>
void myraylib(int width, int height, const char* title, const int fps,
	// App constructor parameters
	Args &&... args
) {
	raylib::Window window(width, height, title);

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

