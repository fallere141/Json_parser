//
// Created by Fallere141 on 5/18/24.
//

#include <map>


#include "json4.h"
#include "json5.h"
#include "json6.h"

using namespace std;
using namespace final;
int main(){
    Json< Json_temp<std::tuple<type_pair<"first", int>, type_pair<"second", int>, type_pair<"third",int>>>> json_try{};
    json_try.parser(R"({"first":3,"second":5,"third":4})");
    std::cout<<json_try.to_string()<<std::endl;

    Json< Json_temp<std::tuple<type_pair<"first", std::string>, type_pair<"second", int>, type_pair<"third",int>>>> json_try2{};
    json_try2.parser(R"({"first":"hello","second":5,"third":4})");
    std::cout<<json_try2.to_string()<<std::endl;
//    auto i = get_Json<"first">(json_try2.json_container);
    std::cout<<json_try2.get_Json<"first">().val;


}