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

    Json_temp<tuple<type_pair<"first", int>, type_pair<"second", double>>> tryJsonTemp{2, 3.5};
    Json_temp<std::tuple<type_pair<"first", int>, type_pair<"second", double>, type_pair<"third",int>>> tryJsonTemp2{};
    set_Json<"first">(tryJsonTemp2, 7);
    set_Json<"second">(tryJsonTemp2, 7.9);
    set_Json<"third">(tryJsonTemp2,2);
    std::string third = "third";
    std::string first = "first";
    set_str(tryJsonTemp2,third,10);
    set_str(tryJsonTemp2,first,10);
    auto i = get_Json<"third">(tryJsonTemp2);
    cout<<i.val<<endl;
    auto ii = get_Json<"first">(tryJsonTemp2);
    cout<<ii.val<<endl;
    std::cout<<value_haskey(tryJsonTemp2,"f")<<std::endl;
    std::cout<<value_haskey(tryJsonTemp2,first)<<std::endl;
    std::cout<<get_Json_str(tryJsonTemp2)<<std::endl;
    Json< Json_temp<std::tuple<type_pair<"first", int>, type_pair<"second", double>, type_pair<"third",int>>>> json_try{};
    json_try.parser(R"({"first":3,"second":5.5,"third":4})");
//    json_try.parser();
}