//
// Created by Fallere141 on 5/7/24.
//

#include "json.h"
using namespace std;
using namespace final;
int main(){


    std::cout << "Hello, World!" << std::endl;
    static_assert(is_same_v<float, GetTupleType<1,tuple<int, float,double>>::type>);

    JSON<> init;
    init["hello"] = "1";

    init.get("hello");


}