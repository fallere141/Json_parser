//
// Created by Fallere141 on 5/7/24.
//

#ifndef JSON_DECODE_JSON_H
#define JSON_DECODE_JSON_H
#include <map>
#include <string>
#include <tuple>
#include <iostream>
using std::cout;
using std::endl;

namespace final {

    template<int i, typename ...Ts>
    struct GetTupleType;

    template<int i, typename T,typename ...Ts>
    struct GetTupleType<i,std::tuple<T,Ts ...>>{
        using type = typename GetTupleType<i-1,std::tuple<Ts ...>>::type;
    };

    template<typename T,typename ...Ts>
    struct GetTupleType<0,std::tuple<T,Ts ...>>{
        using type = T;
    };

    template<typename ... T>
    struct Append;

    template<typename ...Ts1, typename ... Ts2>
    struct Append<std::tuple<Ts1...>,std::tuple<Ts2...>>{
        using type = std::tuple<Ts1 ... , Ts2 ...>;
    };









    template<typename T>
    T StringtoT(std::string str);

    template<>
    std::string StringtoT<std::string>(std::string str){
        cout<<"is a string"<<endl;
        return str;
    }

    template<>
    int StringtoT<int>(std::string str){
        cout<<"is a int"<<endl;
        return -1;
    }

    template<>
    double StringtoT<double>(std::string str){
        cout<<"is a double"<<endl;
        return -1.1;
    }

    template<typename ... types>
    struct JSON{
        std::map<std::string,std::string> dict_pairs;
        using type = typename std::tuple<types ...>;
        auto get(std::string var){
//            StringtoT<>
            return StringtoT<GetTupleType<0,type>::type>>(dict_pairs[var]);
//            return dict_pairs[var];
        }

        template<class T>
        std::string& operator[](T index){
            auto it = dict_pairs.find(index);
            if(it==dict_pairs.end()){
                using type =typename Append<type,std::tuple<T>>::type;
            }
            return dict_pairs[index];
        }

    };





}


#endif //JSON_DECODE_JSON_H
