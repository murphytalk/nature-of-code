#include <raylib-cpp.hpp>
#include <vector>
#include <thread>

class sort {
    std::thread sorting1;
    std::thread sorting2;
    std::vector<int> items1;
    std::vector<int> items2;
    int bar_width;
    float bar_height_unit;
    void draw_sorting_bars(const raylib::Color& clr, int screenWidth, int screenHeight, const std::vector<int>& items);
public:
    sort(int w, int h, int b);
    void update(raylib::Window &window, int screenWidth, int screenHeight);
    void draw(raylib::Window &window, int screenWidth, int screenHeight);
};
