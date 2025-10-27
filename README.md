# EvaLLVM
---
EvaLLVM is a small toy compiler built using LLVM.  
It is developed as part of a learning project to explore how high-level language constructs can be translated into LLVM Intermediate Representation (IR).

---

## 🚀 Overview

EvaLLVM demonstrates how a simple Lisp-like language can be compiled into LLVM Intermediate Representation (IR).  
It provides a minimal but clear example of how to build a front end that generates LLVM IR for core language features such as variables, arithmetic, and control flow. The project follows the design of the Eva language compiler introduced in Dmitry Soshnikov’s educational course on compiler construction.

---

## 🛠️ Build Instructions

Make sure you have **LLVM 14** installed.

to compile and run the project, simply execute:

```bash
./compile-run.sh
```
The script compiles the source code and runs the generated LLVM IR automatically.
