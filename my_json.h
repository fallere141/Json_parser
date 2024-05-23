//
// Created by Fallere141 on 5/17/24.
//

#ifndef JSON_DECODE_MY_JSON_H
#define JSON_DECODE_MY_JSON_H

#include "json_parser.h"
#include "json_container.h"
#include <cassert>
#include <concepts>

namespace final {

    //https://stackoverflow.com/questions/68443804/c20-concept-to-check-tuple-like-types
    template<typename T>
    struct is_type_pair : std::false_type {};

    template<ctll::fixed_string Name, typename T>
    struct is_type_pair<type_pair<Name,T>> : std::true_type {};

    template<typename T>
    concept is_type_pair_t = is_type_pair<T>::value;

    template<typename T>
    struct json_impl : std::false_type {};

    template<is_type_pair_t T>
    struct json_impl<std::tuple<T>> {
        static constexpr bool value = true;
    };

    template<is_type_pair_t... Ts>
    struct json_impl<std::tuple<Ts...>>:std::true_type {};

    template<class T>
    concept json_type = json_impl<T>::value;

    template<json_type T>
    struct Json {
        Json_container<T> json_container;
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
