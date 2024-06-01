#include "Color.hpp"
#include "Rectangle.hpp"
#include "play.hxx"
#include "raylib.h"
#include <random>
#include <algorithm>
#include <iterator> // for std::iterator_traits

using namespace std::chrono_literals;

namespace {
    int random_v(int min, int max){
        static std::random_device rd;
        static std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(mt);
    }

    template<class RandomIt, class Compare>
    void bubble_sort(RandomIt first, RandomIt last, Compare comp) {
        using ValueType = typename std::iterator_traits<RandomIt>::value_type;
        bool swapped = true;
        while (swapped) {
            swapped = false;
            for (RandomIt it = first; it != last - 1; ++it) {
                if (comp(*(it + 1), *it)) {
                    std::iter_swap(it, it + 1);
                    swapped = true;
                }
            }
            --last; // Each pass through the list places the next largest element in its correct position
        }
    }

    constexpr auto delay_before_sorting = 300ms;
    constexpr auto draw_delay = 1ms;
    constexpr int space_between_bar = 1; // space between bars
    constexpr int frame_margin = 2;
}

sort::sort(int w, int h, int b): running(-1){
    /*  let n be num of bars
     *  
     *  n * b + (n-1) * s = w
     */
    // arrange 2 sorting areas vertically
    w -= 2*frame_margin;
    h = (h-frame_margin) / 2;
    const int n = (w + space_between_bar)/(b + space_between_bar);
    bar_width = (w - (n-1)*space_between_bar) / n;
    bar_height_unit = (float)h / n;

    rc1 = raylib::Rectangle(frame_margin, frame_margin, w,h);
    rc2 = raylib::Rectangle(frame_margin, frame_margin + h + frame_margin, w,h);

    items1.reserve(n);
    items2.reserve(n);

    for(int i = 0 ;i < n; ++i){
        auto v = random_v(1, n);
        items1.push_back(v);
        items2.push_back(v);
    }
}

void sort::start(){
    if(sorting1.joinable()) return;

    auto cmp = [](int a, int b){
        std::this_thread::sleep_for(draw_delay);
        return a < b;
    };
    sorting1 = std::thread([this,&cmp](){
        running++;
        TraceLog(LOG_INFO,"running sorting: %d", (int)running);
        std::sort(items1.begin(), items1.end(),cmp);
        running--;
        TraceLog(LOG_INFO,"running sorting: %d", (int)running);
    });

    sorting2 = std::thread([this,&cmp](){
        running++;
        TraceLog(LOG_INFO,"running sorting: %d", (int)running);
        bubble_sort(items2.begin(), items2.end(),cmp);
        running--;
        TraceLog(LOG_INFO,"running sorting: %d", (int)running);
    });
}

void sort::update(raylib::Window& window, int screenWidth, int screenHeight){
    if(running <= 0 && IsKeyPressed(KEY_SPACE)){
        running = 0;
        start();
    }
}

void sort::draw_sorting_bars(const raylib::Color& clr){
    for(int i = 0 ; i < items1.size() ; ++i){
        draw_one_sorting_bar(clr, "std::sort", rc1, items1, i);
        draw_one_sorting_bar(clr, "bubble sort", rc2,  items2, i);
    }
}

void sort::draw_one_sorting_bar(const raylib::Color& clr, const char* sort_name, raylib::Rectangle& rc,const std::vector<int>& items, int i){
    clr.DrawText(sort_name,frame_margin , rc.y + frame_margin, 10);
    int barHeight = items[i] * bar_height_unit;
    clr.DrawRectangle(i * (bar_width + 1), rc.y + rc.height - barHeight, bar_width, barHeight);
}

void sort::draw(raylib::Window& window, int screenWidth, int screenHeight){
    ClearBackground(RAYWHITE);
    if(running < 0){
        raylib::Color foreground(0, 68, 130);
        constexpr char txt[] = "Press space to run";
        constexpr int font_size = 50;
        const auto textWidth = MeasureText(txt, font_size);
        float posX = (screenWidth - textWidth) / 2.0f;
        float posY = (screenHeight - font_size) / 2.0f;
        foreground.DrawText(txt, posX, posY, font_size);
    }
    else{
        draw_sorting_bars(BLACK);
    }
}
