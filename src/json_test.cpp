#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

int main()
{
    std::ifstream f("test.json");
    json data = json::parse(f);
    for (const auto &element : data["test_array"]) {
        auto s_str = element["question"]["answer"].get<string>();
        auto str = element["question"]["text"].get<string>();
        cout << str << '\n';
        cout << s_str << '\n';
        cout << element["question"]["variants"] << '\n';
    }
}
