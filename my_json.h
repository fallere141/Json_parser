//
// Created by Fallere141 on 5/17/24.
//

#ifndef JSON_DECODE_MY_JSON_H
#define JSON_DECODE_MY_JSON_H

#include "json_parser.h"
#include "json_container.h"
#include <cassert>

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
        };

        template<ctll::fixed_string Name>
        auto get(){
            return get_Json<Name>(json_container);
        }

        template<ctll::fixed_string Name,typename target_type>
        auto set(target_type const &val){
            return set_Json<Name>(json_container, val);
        }

        template<ctll::fixed_string Name>
        auto hasKey(){
            return hasKey<Name>(json_container);
        }

    };
}
#endif //JSON_DECODE_MY_JSON_H
