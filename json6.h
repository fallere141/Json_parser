//
// Created by Fallere141 on 5/17/24.
//

#ifndef JSON_DECODE_JSON6_H
#define JSON_DECODE_JSON6_H

#include "json4.h"
#include "json5.h"

namespace std{
    template<class _CharT, class _Traits, class _Allocator>
    class basic_string{
        operator int(){
            return 0;
        }
        operator double (){
            return 0;
        }
    };
}


namespace final {

    template<typename T>
    struct Json {
        T json_container;
        Json():json_container{} {};

        void parser(std::string const &json_str) {
            Json_parser json_parser(json_str);
            for (const auto &pair: json_parser.json_pair) {
                if (value_haskey(json_container, pair.first)) {
                    if (std::holds_alternative<int>(pair.second)) {
                        set_str(json_container, pair.first, std::get<int>(pair.second));

                    } else if (std::holds_alternative<double>(pair.second)) {
                        set_str(json_container, pair.first, std::get<double>(pair.second));
                    } else if (std::holds_alternative<std::string>(pair.second)){
                        std::string value = std::get<std::string>(pair.second);
                        set_str_str(json_container, pair.first, value);
                    }
                }
            }
        }

        std::string to_string(){
            return get_Json_str(json_container);
        }

//        template<ctll::fixed_string Name>
//        auto get_Json(){
//            return get_Json<Name>(json_container);
//        }

    };
//    template<ctll::fixed_string Name>
//    auto get(){
//        return get_Json<Name>(json_container);
//    }

}
#endif //JSON_DECODE_JSON6_H
