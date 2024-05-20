//
// Created by Fallere141 on 5/16/24.
//

#ifndef JSON_DECODE_JSON5_H
#define JSON_DECODE_JSON5_H

#include <ctre.hpp>
#include <iostream>
#include <string>
#include <string_view>
#include "json4.h"
//#include "json6.h"

namespace final {

    template<ctll::fixed_string Name, typename T>
    struct type_pair {
    public:
        type_pair(T const &t) : val(t) {};

        type_pair() {};
        T val;
    };

    template<ctll::fixed_string Name>
    struct key_value {

        std::string convertCtllString2String(std::basic_string_view<char32_t> str) {
            std::string result(str.begin(), str.end());
            return result;
        }

        std::string get_string() {
            return convertCtllString2String(std::basic_string_view<char32_t>(Name));
        }

        template<size_t N>
        ctll::fixed_string<N> get_fixed_string() {
            return Name;
        }
    };

    template<typename T, ctll::fixed_string ... Names>
    struct Json_temp;

    template<typename T, ctll::fixed_string Name>
    struct Json_temp<std::tuple<type_pair<Name, T>>> {
        using type = typename std::tuple<type_pair<Name, T>>;

        using key_tuple = typename std::tuple<key_value<Name>>;

        Json_temp(T const &t) : val(t) {};

        Json_temp() : val() {};
        type_pair<Name, T> val;
    };

    template<ctll::fixed_string ...Names, ctll::fixed_string Name, typename ... Ts, typename T>
    struct Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>>
            : public Json_temp<std::tuple<type_pair<Names, Ts>...>> {
        Json_temp(T const &t, Ts const &... ts) : Json_temp<std::tuple<type_pair<Names, Ts>...>>(ts...), val(t) {};

        Json_temp() : Json_temp<std::tuple<type_pair<Names, Ts>...>>(), val() {};

        using type = typename std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>;
        using key_tuple = typename std::tuple<key_value<Name>, key_value<Names>...>;

        type_pair<Name, T> val;
    };

    template<ctll::fixed_string target, typename T, ctll::fixed_string ... Names>
    struct Getter2;

    template<ctll::fixed_string target, typename ... Ts, ctll::fixed_string ... Names, typename T, ctll::fixed_string Name>
    struct Getter2<target, Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>>> {
        static auto &get(Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>> &tup) {

            return Getter2<target, Json_temp<std::tuple<type_pair<Names, Ts>...>>>::get(
                    static_cast<Json_temp<std::tuple<type_pair<Names, Ts>...>> &> (tup));
        }

        static bool hasKey(Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>> &tup) {
            return Getter2<target, Json_temp<std::tuple<type_pair<Names, Ts>...>>>::hasKey(
                    static_cast<Json_temp<std::tuple<type_pair<Names, Ts>...>> &> (tup));
        }
    };

    template<ctll::fixed_string target, typename ... Ts, ctll::fixed_string ... Names, typename T>
    struct Getter2<target, Json_temp<std::tuple<type_pair<target, T>, type_pair<Names, Ts>...>>> {
        static auto &get(Json_temp<std::tuple<type_pair<target, T>, type_pair<Names, Ts>...>> &tup) {
            return tup.val;
        }

        static bool hasKey(Json_temp<std::tuple<type_pair<target, T>, type_pair<Names, Ts>...>> &tup) {
            return true;
        }
    };

    template<ctll::fixed_string target, typename T>
    struct Getter2<target, Json_temp<std::tuple<type_pair<target, T>>>> {
        static bool hasKey(Json_temp<std::tuple<type_pair<target, T>>> &tup) {
            return true;
        }

        static auto &get(Json_temp<std::tuple<type_pair<target, T>>> &tup) {
            return tup.val;
        }
    };

    template<ctll::fixed_string target, typename T, ctll::fixed_string Name>
    struct Getter2<target, Json_temp<std::tuple<type_pair<Name, T>>>> {
        static bool hasKey(Json_temp<std::tuple<type_pair<Name, T>>> &tup) {
            return false;
        }
    };

    template<ctll::fixed_string target, typename ... Ts, ctll::fixed_string ... Names>
    auto &
    get_Json(Json_temp<std::tuple<type_pair<Names, Ts>...>> &tup) {
        return Getter2<target, Json_temp<std::tuple<type_pair<Names, Ts>...>>>::get(tup);
    }


    template<ctll::fixed_string target, typename ... Ts, ctll::fixed_string ... Names>
    bool
    hasKey(Json_temp<std::tuple<type_pair<Names, Ts>...>> &tup) {
        return Getter2<target, Json_temp<std::tuple<type_pair<Names, Ts>...>>>::hasKey(tup);
    }

    template<ctll::fixed_string target, typename target_type, typename T, ctll::fixed_string ... Names>
    struct setter;

    template<ctll::fixed_string target, typename target_type, typename ... Ts, ctll::fixed_string ... Names, typename T, ctll::fixed_string Name>
    struct setter<target, target_type, Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>>> {
        static void
        set(Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>> &tup, target_type const &val) {

            return setter<target, target_type, Json_temp<std::tuple<type_pair<Names, Ts>...>>>::set(
                    static_cast<Json_temp<std::tuple<type_pair<Names, Ts>...>> &> (tup), val);
        }

    };

    template<ctll::fixed_string target, typename target_type, typename ... Ts, ctll::fixed_string ... Names, typename T>
    struct setter<target, target_type, Json_temp<std::tuple<type_pair<target, T>, type_pair<Names, Ts>...>>> {
        static void
        set(Json_temp<std::tuple<type_pair<target, T>, type_pair<Names, Ts>...>> &tup, target_type const &val) {
            tup.val.val = val;
        }

    };

    template<ctll::fixed_string target, typename target_type, typename ... Ts, ctll::fixed_string ... Names>
    void
    set_Json(Json_temp<std::tuple<type_pair<Names, Ts>...>> &tup, target_type const &val) {
        setter<target, target_type, Json_temp<std::tuple<type_pair<Names, Ts>...>>>::set(tup, val);
    }

    ///////////////////////
    template<typename target_type, typename T, ctll::fixed_string ... Names>
    struct Json_str_set;

    template<typename target_type, typename ... Ts, ctll::fixed_string ... Names, typename T, ctll::fixed_string Name>
    struct Json_str_set<target_type, Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>>> {
        void
        set_with_str(Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>> &tup, std::string const &forKey,
                     target_type const &val) {
            std::string result(std::basic_string_view<char32_t>(Name).begin(),
                               std::basic_string_view<char32_t>(Name).end());
            if (result == forKey) {
                tup.val.val = val;
                return;
            }
            Json_str_set<target_type, Json_temp<std::tuple<type_pair<Names, Ts>...>>> util;
            util.set_with_str(static_cast<Json_temp<std::tuple<type_pair<Names, Ts>...>> &> (tup), forKey, val);
        };
    };

    template<typename target_type, typename T, ctll::fixed_string Name>
    struct Json_str_set<target_type, Json_temp<std::tuple<type_pair<Name, T>>>> {
        void set_with_str(Json_temp<std::tuple<type_pair<Name, T>>> &tup, std::string const &forKey,
                          target_type const &val) {

            std::string result(std::basic_string_view<char32_t>(Name).begin(),
                               std::basic_string_view<char32_t>(Name).end());
            if (result == forKey) {
                tup.val.val = val;
            }
            return;
        };
    };

    template<typename target_type, typename ... Ts, ctll::fixed_string ... Names>
    void
    set_str(Json_temp<std::tuple<type_pair<Names, Ts>...>> &tup, std::string const &forKey, target_type const &val) {
        Json_str_set<target_type, Json_temp<std::tuple<type_pair<Names, Ts>...>>> util;
        util.set_with_str(tup, forKey, val);
    };
//////sting
    template<typename target_type, typename T, ctll::fixed_string ... Names>
    struct Json_str_set_str;

    template<typename ... Ts, ctll::fixed_string ... Names, typename T, ctll::fixed_string Name>
    struct Json_str_set_str<std::string , Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>>> {
        void
        set_with_str(Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>> &tup, std::string const &forKey,
                     std::string const &val) {
            Json_str_set_str<std::string, Json_temp<std::tuple<type_pair<Names, Ts>...>>> util;
            util.set_with_str(static_cast<Json_temp<std::tuple<type_pair<Names, Ts>...>> &> (tup), forKey, val);
        };
    };

    template<typename ... Ts, ctll::fixed_string ... Names, ctll::fixed_string Name>
    struct Json_str_set_str<std::string , Json_temp<std::tuple<type_pair<Name, std::string>, type_pair<Names, Ts>...>>> {
        void
        set_with_str(Json_temp<std::tuple<type_pair<Name, std::string>, type_pair<Names, Ts>...>> &tup, std::string const &forKey,
                     std::string const &val) {
            std::string result(std::basic_string_view<char32_t>(Name).begin(),
                               std::basic_string_view<char32_t>(Name).end());
            if (result == forKey) {
                tup.val.val = val;
                return;
            }

            Json_str_set_str<std::string, Json_temp<std::tuple<type_pair<Names, Ts>...>>> util;
            util.set_with_str(static_cast<Json_temp<std::tuple<type_pair<Names, Ts>...>> &> (tup), forKey, val);
        };
    };

    template<typename T, ctll::fixed_string Name>
    struct Json_str_set_str<std::string,Json_temp<std::tuple<type_pair<Name, T>>>> {
        void set_with_str(Json_temp<std::tuple<type_pair<Name, T>>> &tup, std::string const &forKey,
                          std::string const &val) {
            return;
        };
    };

    template<ctll::fixed_string Name>
    struct Json_str_set_str<std::string,Json_temp<std::tuple<type_pair<Name, std::string>>>> {
        void set_with_str(Json_temp<std::tuple<type_pair<Name, std::string>>> &tup, std::string const &forKey,
                          std::string const &val) {
            std::string result(std::basic_string_view<char32_t>(Name).begin(),
                               std::basic_string_view<char32_t>(Name).end());
            if (result == forKey) {
                tup.val.val = val;
            }
            return;
        };
    };


    template<typename ... Ts, ctll::fixed_string ... Names>
    void
    set_str_str(Json_temp<std::tuple<type_pair<Names, Ts>...>> &tup, std::string const &forKey, std::string const &val) {
        Json_str_set_str<std::string,Json_temp<std::tuple<type_pair<Names, Ts>...>>> util;
        util.set_with_str(tup, forKey, val);
    };
/////////////////
    template<typename T, ctll::fixed_string ... Names>
    struct Json_str_haskey;

    template<typename ... Ts, ctll::fixed_string ... Names, typename T, ctll::fixed_string Name>
    struct Json_str_haskey<Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>>> {
        bool set_with_str(Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>> &tup,
                          std::string const &forKey) {
            std::string result(std::basic_string_view<char32_t>(Name).begin(),
                               std::basic_string_view<char32_t>(Name).end());
            if (result == forKey) {

                return true;
            } else {

                Json_str_haskey<Json_temp<std::tuple<type_pair<Names, Ts>...>>> util;
                return util.set_with_str(static_cast<Json_temp<std::tuple<type_pair<Names, Ts>...>> &> (tup), forKey);
            }
        };
    };

    template<typename T, ctll::fixed_string Name>
    struct Json_str_haskey<Json_temp<std::tuple<type_pair<Name, T>>>> {
        bool set_with_str(Json_temp<std::tuple<type_pair<Name, T>>> &tup, std::string const &forKey) {

            std::string result(std::basic_string_view<char32_t>(Name).begin(),
                               std::basic_string_view<char32_t>(Name).end());
            if (result == forKey) {
                return true;
            }
            return false;
        };
    };

    template<typename ... Ts, ctll::fixed_string ... Names>
    bool
    value_haskey(Json_temp<std::tuple<type_pair<Names, Ts>...>> &tup, std::string const &forKey) {
        Json_str_haskey<Json_temp<std::tuple<type_pair<Names, Ts>...>>> util;
        return util.set_with_str(tup, forKey);
    };
    ///////////////////

    template<typename T, ctll::fixed_string ... Names>
    struct Json_turn_str;

    template<typename ... Ts, ctll::fixed_string ... Names, typename T, ctll::fixed_string Name>
    struct Json_turn_str<Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>>> {
        std::string get_Json_str(Json_temp<std::tuple<type_pair<Name, T>, type_pair<Names, Ts>...>> &tup) {
            std::string key(std::basic_string_view<char32_t>(Name).begin(),
                            std::basic_string_view<char32_t>(Name).end());
            Json_turn_str<Json_temp<std::tuple<type_pair<Names, Ts>...>>> util;

            return std::format("\"{}\":{},", key, tup.val.val) +
                   util.get_Json_str(static_cast<Json_temp<std::tuple<type_pair<Names, Ts>...>> &> (tup));
        };
    };

    template<typename ... Ts, ctll::fixed_string ... Names, ctll::fixed_string Name>
    struct Json_turn_str<Json_temp<std::tuple<type_pair<Name, std::string>, type_pair<Names, Ts>...>>> {
        std::string get_Json_str(Json_temp<std::tuple<type_pair<Name, std::string>, type_pair<Names, Ts>...>> &tup) {
            std::string key(std::basic_string_view<char32_t>(Name).begin(),
                            std::basic_string_view<char32_t>(Name).end());
            Json_turn_str<Json_temp<std::tuple<type_pair<Names, Ts>...>>> util;

            return std::format("\"{}\":\"{}\",", key, tup.val.val) +
                   util.get_Json_str(static_cast<Json_temp<std::tuple<type_pair<Names, Ts>...>> &> (tup));
        };
    };

    template<typename T, ctll::fixed_string Name>
    struct Json_turn_str<Json_temp<std::tuple<type_pair<Name, T>>>> {

        std::string get_Json_str(Json_temp<std::tuple<type_pair<Name, T>>> &tup) {
            std::string key(std::basic_string_view<char32_t>(Name).begin(),
                            std::basic_string_view<char32_t>(Name).end());
            return std::format("\"{}\":{},", key, tup.val.val);
        };
    };

    template<ctll::fixed_string Name>
    struct Json_turn_str<Json_temp<std::tuple<type_pair<Name, std::string>>>> {

        std::string get_Json_str(Json_temp<std::tuple<type_pair<Name, std::string>>> &tup) {
            std::string key(std::basic_string_view<char32_t>(Name).begin(),
                            std::basic_string_view<char32_t>(Name).end());
            return std::format("\"{}\":\"{}\",", key, tup.val.val);
        };
    };

//
    template<typename ... Ts, ctll::fixed_string ... Names>
    std::string get_Json_str(Json_temp<std::tuple<type_pair<Names, Ts>...>> &tup) {
        Json_turn_str<Json_temp<std::tuple<type_pair<Names, Ts>...>>> util;
        return "{" + util.get_Json_str(tup) + "}";
    };

}
//ctll::fixed_string Name
#endif //JSON_DECODE_JSON5_H
