#include "Color.hpp"
#include "play.hxx"
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

}

sort::sort(int w, int h, int b){
    /*  let n be num of bars
     *  
     *  n * b + (n-1) * s = w
     */
    const int n = (w + space_between_bar)/(b + space_between_bar);
    bar_width = (w - (n-1)*space_between_bar) / n;
    bar_height_unit = (float)h / n;

    items1.reserve(n);
    items2.reserve(n);

    for(int i = 0 ;i < n; ++i){
        auto v = random_v(1, n);
        items1.push_back(v);
        items2.push_back(v);
    }

    auto cmp = [](int a, int b){
        std::this_thread::sleep_for(draw_delay);
        return a < b;
    };
    sorting1 = std::thread([this,&cmp](){
        std::this_thread::sleep_for(delay_before_sorting);
        bubble_sort(items1.begin(), items1.end(),cmp);
    });
#if 0
    std::thread s2([this,&cmp](){
        std::this_thread::sleep_for(delay_before_sorting);
        bubble_sort(items2.begin(), items2.end(),cmp);
    });
#endif
}

void sort::update(raylib::Window& window, int screenWidth, int screenHeight){}

void sort::draw_sorting_bars(const raylib::Color& clr, int screenWidth, int screenHeight, const std::vector<int>& items){
    for(int i = 0 ;i < items.size() ;++i){
        int barHeight = items[i] * bar_height_unit;
        clr.DrawRectangle(i * (bar_width + 1), screenHeight - barHeight, bar_width, barHeight);
    }
}
void sort::draw(raylib::Window& window, int screenWidth, int screenHeight){
    ClearBackground(RAYWHITE);
    draw_sorting_bars(BLACK, screenWidth, screenHeight, items1);
}
