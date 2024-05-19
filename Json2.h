//
// Created by Fallere141 on 5/16/24.
//

#ifndef JSON_DECODE_JSON2_H
#define JSON_DECODE_JSON2_H
#include <map>
#include <tuple>
namespace final{
    //utils
    template<typename ... T>
    struct Append;

    template<typename ...Ts1, typename ... Ts2>
    struct Append<std::tuple<Ts1...>,std::tuple<Ts2...>>{
        using type = std::tuple<Ts1 ... , Ts2 ...>;
    };


    template<int i,typename T>
    struct indexItem{};


    template<typename T>
    struct Json{
        using type = T;
    };

    struct JsonType{




    };





//json<std::string:type,...>


}
#endif //JSON_DECODE_JSON2_H
