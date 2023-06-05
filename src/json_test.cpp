#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
int main()
{
    std::ifstream f("test.json");
    json data = json::parse(f);
    std::cout << data;
}
