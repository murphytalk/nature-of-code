#pragma once
#include "CLI/CLI.hpp"
#include <Color.hpp>
#include <Window.hpp>
#include <any>
#include <functional>
#include <map>
#include <memory>
#include <raylib.h>
#include <sstream>
#include <string>
#include <vector>
#include <CLI/CLI.hpp>

template <class App, typename... Args>
void myraylib(int width, int height, const char *title, const int fps,
        unsigned int flags,
        // App constructor parameters
        Args &&...args) {
    /* On Linux if we do not hide window first and then clear the hidden flag after
     * initialization the window won't display. Possible reasons:
     *  - Initialization Timing
     *  - Compositor Interaction
     *  - GLFW Behavior
     */
#ifdef __linux__
    flags |= FLAG_WINDOW_HIDDEN;
#endif
    raylib::Window window(width, height, title, flags);
#ifdef __linux__
    ClearWindowState(FLAG_WINDOW_HIDDEN);
#endif
    auto app = std::make_unique<App>(std::forward<Args>(args)...);

    SetTargetFPS(fps);
    while (!window.ShouldClose()) { // Detect window close button or ESC key
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

template <typename T> T from_string(const std::string &str) {
    std::istringstream iss(str);
    T value;
    iss >> value;
    return value;
}

using FuncType = std::function<void(const std::vector<std::string> &)>;
struct AppDef{
    const int param_num;
    const char* help;
    const FuncType func;
};

using FuncMap = std::map<std::string, AppDef>;

#define print_app_help(name,help) \
    std::cout << "-a " << name << " " << help << std::endl;

inline void callFunctionByName(const FuncMap &functionMap,
        const std::string &name,
        const std::vector<std::string> &args) {
    auto it = functionMap.find(name);
    if (it != functionMap.end()) {
        if(it->second.param_num != args.size()){
            print_app_help(name,it->second.help);
        }
        else{
            it->second.func(args);
        }
    }
}

inline const std::pair<std::string, std::vector<std::string>> parse_cmd_line_args(const char* title,int argc, char** argv,const FuncMap &functionMap){
    CLI::App app {title};
    argv = app.ensure_utf8(argv);

    std::string app_name;
    bool list = false;
    auto list_flag = app.add_flag("-l", list, "list all apps");
    auto app_opt = app.add_option("-a", app_name, "app to run");
    std::vector<std::string> app_args;
    app.add_option("args", app_args, "arguments for specified app");

    list_flag->excludes(app_opt);
    app_opt->excludes(list_flag);

    try {
        app.parse(argc, argv);
    } catch(const CLI::ParseError &e) {
        exit(app.exit(e));
    }
    if(list){
        for(auto const& a: functionMap){
            print_app_help(a.first, a.second.help);
        }
        exit(0);
    }
    return std::make_pair(app_name, app_args);
}
