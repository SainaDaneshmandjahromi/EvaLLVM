#include "./EvaLLVM.h"

#include <string>

int main(){

    std::string program = R"(

    (class Point null
        (begin
            (var x 0)
            (var y 0)
        )        
    )   
    )";

    EvaLLVM vm;

    vm.exec(program);

    return 0;
}