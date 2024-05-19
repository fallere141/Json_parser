//
// Created by Fallere141 on 5/17/24.
//

#ifndef JSON_DECODE_JSON6_H
#define JSON_DECODE_JSON6_H

#include "json4.h"
#include "json5.h"

namespace final {

//    std::string convertCtllString2String(std::basic_string_view<char32_t> str){
//        std::string result(str.begin(), str.end());
//        return result;
//    }


//    ctll::fixed_string<> string2ctll(std::string str){
//
//    }




    template<typename T>
    struct Json {
        T json_container;

        Json():json_container() {};

        void parser(std::string const &json_str) {
            Json_parser json_parser(json_str);
            for (const auto &pair: json_parser.json_pair) {
                if (value_haskey(json_container, pair.first)) {
                    if (std::holds_alternative<int>(pair.second)) {
                        set_str(json_container, pair.first, std::get<int>(pair.second));

                    } else if (std::holds_alternative<double>(pair.second)) {
                        set_str(json_container, pair.first, std::get<double>(pair.second));

                    } else {
//                        std::string value = std::get<std::string>(pair.second);
//                        set_str(json_container, pair.first, value);
                    }
                }
            }
        }
    };


}
#endif //JSON_DECODE_JSON6_H
