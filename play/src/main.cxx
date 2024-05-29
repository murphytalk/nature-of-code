#include "play.hxx"
#include "app.hxx"

FuncMap apps = {
    {"sort", AppDef {3, "<screen width> <screen height> <bar width>", 
        [](const std::vector<std::string>& args){
            const int w = from_string<int>(args[0]);
            const int h = from_string<int>(args[1]);
            const int b = from_string<int>(args[2]);
            myraylib<sort>(w, h, "Visualize sorting", 60, 0, w, h, b);
        }},
    },
};

int main(int argc, char** argv)
{
    const auto& args = parse_cmd_line_args("My playground", argc, argv,apps);
    callFunctionByName(apps, args.first, args.second);
    return 0;
}
