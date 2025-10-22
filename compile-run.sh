 /usr/bin/clang++ -std=c++17 eva-llvm.cpp -o eva-llvm \
  $(/opt/homebrew/opt/llvm@14/bin/llvm-config --cxxflags --ldflags --system-libs --libs core)


./eva-llvm

lli ./out.ll

