; ModuleID = 'EvaLLVM'
source_filename = "EvaLLVM"

@VERSION = global i32 42, align 4
@0 = private unnamed_addr constant [6 x i8] c"Hello\00", align 1
@1 = private unnamed_addr constant [8 x i8] c"X: %s\0A\0A\00", align 1
@2 = private unnamed_addr constant [8 x i8] c"X: %d\0A\0A\00", align 1
@3 = private unnamed_addr constant [8 x i8] c"X: %d\0A\0A\00", align 1
@4 = private unnamed_addr constant [18 x i8] c"Is X == 100?: %d\0A\00", align 1

declare i32 @printf(i8*, ...)

define i32 @main() {
entry:
  %z = alloca i32, align 4
  store i32 32, i32* %z, align 4
  %z1 = load i32, i32* %z, align 4
  %tmpadd = add i32 %z1, 10
  %x = alloca i32, align 4
  store i32 %tmpadd, i32* %x, align 4
  %x2 = alloca i8*, align 8
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @0, i32 0, i32 0), i8** %x2, align 8
  %x3 = load i8*, i8** %x2, align 8
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @1, i32 0, i32 0), i8* %x3)
  %x4 = load i32, i32* %x, align 4
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @2, i32 0, i32 0), i32 %x4)
  store i32 100, i32* %x, align 4
  %x5 = load i32, i32* %x, align 4
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @3, i32 0, i32 0), i32 %x5)
  %x6 = load i32, i32* %x, align 4
  %tmpcmp = icmp eq i32 %x6, 100
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @4, i32 0, i32 0), i1 %tmpcmp)
  ret i32 0
}
