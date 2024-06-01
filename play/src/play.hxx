#include "Rectangle.hpp"
#include <raylib-cpp.hpp>
#include <vector>
#include <thread>
#include <atomic>

class sort {
    std::atomic<int> running;
    std::thread sorting1;
    std::thread sorting2;
    std::vector<int> items1;
    std::vector<int> items2;
    raylib::Rectangle rc1;
    raylib::Rectangle rc2;
    int bar_width;
    float bar_height_unit;
    void start();
    void draw_sorting_bars(const raylib::Color& clr);
    void draw_one_sorting_bar(const raylib::Color& clr, raylib::Rectangle& rc, const std::vector<int>& items, int i);
public:
    sort(int w, int h, int b);
    void update(raylib::Window &window, int screenWidth, int screenHeight);
    void draw(raylib::Window &window, int screenWidth, int screenHeight);
};
