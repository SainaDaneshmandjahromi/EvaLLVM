#include "./EvaLLVM.h"

#include <string>

int main(){

    std::string program = R"(
        (var x 42)

        (begin 
            (var (x string) "Hello")
            (printf "X: %s\n\n" x))

        (printf "X: %d\n\n" x)

        (set x 100)
        (printf "X: %d\n\n" x)

    )";

    EvaLLVM vm;

    vm.exec(program);

    return 0;
}