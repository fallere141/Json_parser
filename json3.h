//
// Created by Fallere141 on 5/16/24.
//

#ifndef JSON_DECODE_JSON3_H
#define JSON_DECODE_JSON3_H

#include <string>
#include <map>
#include <utility>
#include <variant>
namespace JsonParser {
    using text_it = std::string::iterator;

    /**
     * @brief A union value representing the value part of (key, value) pair.
     */
    union JsonValue {
        int i;
        double d;
        std::map<std::string, JsonValue>* json;
    };



    void ReadFile(const std::string& filepath, std::string& output);

    JsonValue ParsePrimitive(const std::string& text, text_it start, text_it end);

    std::pair<std::string, JsonValue> RetriveKeyValuePair(
            const std::string& text,
            text_it& it
    );

    JsonValue ParseJsonHelper(const std::string& text, text_it& it);

    JsonValue ParseJson(const std::string& filepath);
}

#endif //JSON_DECODE_JSON3_H
