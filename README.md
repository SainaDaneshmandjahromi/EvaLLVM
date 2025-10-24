# EvaLLVM
---
EvaLLVM is a small toy compiler built using LLVM.  
It is developed as part of a learning project to explore how high-level language constructs can be translated into LLVM Intermediate Representation (IR).

The project follows the design of the Eva language compiler introduced in an educational course on compiler construction.  
---

## 🚀 Overview

EvaLLVM demonstrates how a simple Lisp-like language can be compiled into LLVM Intermediate Representation (IR).  
It provides a minimal but clear example of how to build a front end that generates LLVM IR for core language features such as variables, arithmetic, and control flow.The project follows the design of the *Eva language* compiler introduced in an educational course on compiler construction.  

---

## 🛠️ Build Instructions

Make sure you have **LLVM 14** installed.

Then compile the project using:

```bash
/usr/bin/clang++ -std=c++17 eva-llvm.cpp -o eva-llvm \
  $(/opt/homebrew/opt/llvm@14/bin/llvm-config --cxxflags --ldflags --system-libs --libs core)
```


## ▶️ Running

To execute the compiler and run the generated LLVM code:

```bash
./eva-llvm
lli ./out.ll
echo $?
printf "\n"
```