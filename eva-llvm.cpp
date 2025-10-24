#include "./EvaLLVM.h"

#include <string>

int main(){

    std::string program = R"(

        (var z 32)

        (var x (+ z 10))

        (begin 
            (var (x string) "Hello")
            (printf "X: %s\n\n" x))

        (printf "X: %d\n\n" x)

        (set x 100)
        (printf "X: %d\n\n" x)

        (printf "Is X == 100?: %d\n" (== x 100))

        (if (== x 42)
        
            (set x 100)
            (set x 200))

        (printf "X: %d\n\n" x)

        (while (> x 0)
            (begin
                (set x (- x 1))
                (printf "X: %d\n\n" x)))
    )";

    EvaLLVM vm;

    vm.exec(program);

    return 0;
}