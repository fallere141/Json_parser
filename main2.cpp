//
// Created by Fallere141 on 5/18/24.
//

#include <map>
#include "my_json.h"

using namespace std;
using namespace final;


int main() {
    string text = "{\"tt\":4,\"second\":5,\"third\":4}";
    Json<Json_container<std::tuple<type_pair<"tt", int>, type_pair<"second", int>, type_pair<"third", int>>>> json_try{};
//    json_try.parser(R"({"tt":3,"second":5,"third":4})");
    json_try.parser(text);
    cout<<text<<endl;
    std::cout << json_try.to_string() << std::endl;

    Json<Json_container<std::tuple<type_pair<"first", std::string>, type_pair<"second", int>, type_pair<"third", int>>>> json_try2{};
    json_try2.parser(R"({"first":"hello","second":5,"third":4})");
    std::cout << json_try2.to_string() << std::endl;

    static constexpr ctll::fixed_string first = "first";
    json_try2.set<first>("hello2");
    std::cout << json_try2.get<"first">().val;

}