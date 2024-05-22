//#include <iostream>
#include <map>

#include <type_traits>
#include "json_parser.h"
#include "json_container.h"
#include "my_json.h"

using namespace std;
using namespace final;

template<ctll::fixed_string Name, ctll::fixed_string Name2>
struct template_string {
    void print() {
        std::basic_string_view<char32_t> g = std::basic_string_view<char32_t>(Name);
        std::u32string gg(g);
        for (auto i: gg) {
            std::wcout << (wchar_t) i;
        }
    }

    std::string get_string() {
        return convertCtllString2String(std::basic_string_view<char32_t>(Name));
    }
    void test(std::string str) {


        if (get_string()== str) {
            std::cout<<"Name1"<<std::endl;
        }
        else {
            std::cout<<"Name2"<<std::endl;
        }
    }

    std::variant<key_value<Name>,key_value<Name2>> get_fixed_string(std::string str) {
            if (convertCtllString2String(std::basic_string_view<char32_t>(Name)) == str) {
                return key_value<Name>{};
            }
            else {
                return key_value<Name2>{};
            }
        }
};

template<class T, size_t N, class V>
std::array<T, N> to_array(const V& v)
{
//    assert(v.size() == N);
    std::array<T, N> d;
    using std::begin; using std::end;
    std::copy( begin(v), end(v), begin(d) ); // this is the recommended way
    return d;
}



int main() {

    string jsonStr = R"({"hello":3,"gg":"kkwadw","kk":{"dawd":{"kkk":3},"dadwf":"dadwd"},"ggg":3.5,})";
    Json_parser try1(jsonStr);
    auto try1_str = try1.to_string();

    Json_parser try3(try1_str);
    std::cout << try3.to_string();


    type_pair<"second", double> second(2.3);

    Json_container<tuple<type_pair<"first", int>, type_pair<"second", double>>> tryJsonTemp{2, 3.5};
    Json_container<std::tuple<type_pair<"first", int>, type_pair<"second", double>>> tryJsonTemp2{};

    set_Json<"first">(tryJsonTemp2, 10);
    auto i = get_Json<"first">(tryJsonTemp2);


    std::cout << "\n" << i.val << std::endl;

    template_string<"hello","hallol"> kkkk;
kkkk.test("hello");
    std::cout<<kkkk.get_string()<<std::endl;

    std::basic_string<char32_t> test = U"first";
    char32_t str[6] = U"first";
//    ctll::fixed_string test2{test.data(),test.data()+test.size()};
//    ctll::fixed_string test2{};
    std::cout<<hasKey<"first">(tryJsonTemp2)<<std::endl;
//    std::cout<<hasKey<str>(tryJsonTemp2)<<std::endl;

//    std::string test_str = "hello";
//    std::array<char32_t,30> test_char32_t =to_array<char32_t,30>(test_str);
//    ctll::fixed_string test_ctll_str = kkkk.get_fixed_string("hello");
//    std::cout<<convertCtllString2String(test_ctll_str);
//    std::copy(v.begin(), v.end(), d.data());
    return 0;
}
