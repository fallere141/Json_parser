//
// Created by Fallere141 on 5/16/24.
//

#ifndef JSON_DECODE_JSON4_H
#define JSON_DECODE_JSON4_H

#include <variant>
#include <string>
#include <map>
#include "ctre.hpp"
#include <iostream>
#include <format>
#include "json5.h"

namespace final {
    using jsonType = std::variant<int, double, std::string>;

    struct Json_parser {
    public:
        std::map<std::string, jsonType> json_pair;

    private:
        std::string input;
//        std::map<std::string, jsonType> json_pair;

        void parser() {
            std::string subJson;
            auto keypairs = ctre::search_all<R"((?:\"|')([^"]*)(?:\"|')(?=:)(?::\s*)(?:\")?(true|false|[\-0-9]+[.]*[0-9]*(?=,)|[0-9a-zA-Z.\n\r\t]*)(?:\")?)">(
                    input);
            for (auto keypair: keypairs) {
                if (subJson.find(keypair) != std::string::npos) {
                    continue;
                }

                int index = keypair.to_string().find_last_not_of("\n\r\t");
                if (keypair.to_view()[index] == ':') {
                    subJson = input.substr(input.find(keypair) + keypair.size(), input.size());
                    subJson = subJson.substr(0, findCorrespondingBrackets(subJson));
                    json_pair[keypair.to_string().substr(1, keypair.size() - 3)] = subJson;
                    continue;
                }
                auto result = ctre::match<"(?<key>\"[A-Za-z0-9]+\")[\n\t\r]?:[\n\t\r]?(?<pair>[\"0-9A-Za-z.]+)[\n\t\r]?">(
                        keypair);
                std::string value = result.get<"pair">().to_string();
                if (value.front() == '\"') {
                    json_pair[result.get<"key">().to_string().substr(1, result.get<"key">().to_string().size() -
                                                                        2)] = value.substr(1, value.size() - 2);
                } else if (value.find(".") != std::string::npos) {
                    json_pair[result.get<"key">().to_string().substr(1, result.get<"key">().to_string().size() -
                                                                        2)] = std::stod(value);
                } else {
                    json_pair[result.get<"key">().to_string().substr(1, result.get<"key">().to_string().size() -
                                                                        2)] = std::stoi(value);
                }
            }
        }

        int findCorrespondingBrackets(std::string &str) {
            int index = str.find_first_of("{");
            if (index < 0) {
                return -1;
            }
            ++index;
            int bracketsDifference = 1;
            while (bracketsDifference != 0) {
                index = str.substr(index, str.size()).find_first_of("{}") + 1 + index;
                if (str[index - 1] == '}') {
                    --bracketsDifference;
                } else {
                    ++bracketsDifference;
                }
                if (index > str.size() || bracketsDifference > 30) {
                    return -1;
                }
            }
            return index;
        }

        struct PrintVisitor {
            void operator()(int value) const { std::cout << value << " (int)"; }

            void operator()(double value) const { std::cout << value << " (double)"; }

            void operator()(std::string &value) const { std::cout << value << " (sting)"; }
        };

        struct GetValueVisitor {
            std::string operator()(int value) const { return std::to_string(value); }

            std::string operator()(double value) const { return std::to_string(value); }

            std::string operator()(std::string &value) const { return value; }
        };

        void PrintValue(jsonType value) {
            std::visit(PrintVisitor{}, value);
        }

        std::string variant_to_string(jsonType value) {
            return std::visit(GetValueVisitor{}, value);
        }

    public:
        void print() {
            for (const auto &pair: json_pair) {
                std::cout << "Key: " << pair.first << "\nValue: ";
                PrintValue(pair.second);
                std::cout << std::endl;
            }
        }

        Json_parser(std::string inputStr) {
            input = inputStr;
            parser();
        }

        std::string to_string() {
            std::string jsonStr="{";
            for (const auto &pair: json_pair) {
                if (std::holds_alternative<int>(pair.second)) {
                    jsonStr += std::format("\"{}\":{},", pair.first, std::get<int>(pair.second));

                } else if (std::holds_alternative<double>(pair.second)) {
                    jsonStr += std::format("\"{}\":{},", pair.first, std::get<double>(pair.second));

                } else {
                    std::string value = std::get<std::string>(pair.second);
                    if (value.front() == '{') {
                        jsonStr += std::format("\"{}\":{},", pair.first, value);
                    } else {
                        jsonStr += std::format("\"{}\":\"{}\",", pair.first, value);
                    }
                }
            }
            jsonStr = jsonStr.substr(0,jsonStr.size()-1)+"}";
            return jsonStr;
        }
    };
}
#endif //JSON_DECODE_JSON4_H
