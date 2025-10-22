#include "./EvaLLVM.h"

#include <string>

int main(){

    std::string program = R"(
        (printf "False: %d\n\n" false)
    )";

    EvaLLVM vm;

    vm.exec(program);

    return 0;
}