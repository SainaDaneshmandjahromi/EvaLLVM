; ModuleID = 'EvaLLVM'
source_filename = "EvaLLVM"

@VERSION = global i32 42, align 4
@0 = private unnamed_addr constant [6 x i8] c"Hello\00", align 1
@1 = private unnamed_addr constant [8 x i8] c"X: %s\0A\0A\00", align 1
@2 = private unnamed_addr constant [8 x i8] c"X: %d\0A\0A\00", align 1
@3 = private unnamed_addr constant [8 x i8] c"X: %d\0A\0A\00", align 1
@4 = private unnamed_addr constant [18 x i8] c"Is X == 100?: %d\0A\00", align 1
@5 = private unnamed_addr constant [8 x i8] c"X: %d\0A\0A\00", align 1
@6 = private unnamed_addr constant [8 x i8] c"X: %d\0A\0A\00", align 1

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
  %x7 = load i32, i32* %x, align 4
  %tmpcmp8 = icmp eq i32 %x7, 42
  br i1 %tmpcmp8, label %then, label %else

then:                                             ; preds = %entry
  store i32 100, i32* %x, align 4
  br label %ifend

else:                                             ; preds = %entry
  store i32 200, i32* %x, align 4
  br label %ifend

ifend:                                            ; preds = %else, %then
  %tmpif = phi i32 [ 100, %then ], [ 200, %else ]
  %x9 = load i32, i32* %x, align 4
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @5, i32 0, i32 0), i32 %x9)
  br label %cond

cond:                                             ; preds = %body, %ifend
  %x10 = load i32, i32* %x, align 4
  %tmpcmp11 = icmp ugt i32 %x10, 0
  br i1 %tmpcmp11, label %body, label %loopend

body:                                             ; preds = %cond
  %x12 = load i32, i32* %x, align 4
  %tmpsub = sub i32 %x12, 1
  store i32 %tmpsub, i32* %x, align 4
  br label %cond

loopend:                                          ; preds = %cond
  %5 = call i32 @sum(i32 2, i32 3)
  store i32 %5, i32* %x, align 4
  %x13 = load i32, i32* %x, align 4
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @6, i32 0, i32 0), i32 %x13)
  ret i32 0
}

define i32 @square(i32 %x) {
entry:
  %x1 = alloca i32, align 4
  store i32 %x, i32* %x1, align 4
  %x2 = load i32, i32* %x1, align 4
  %x3 = load i32, i32* %x1, align 4
  %tmpmul = mul i32 %x2, %x3
  ret i32 %tmpmul
}

define i32 @sum(i32 %a, i32 %b) {
entry:
  %a1 = alloca i32, align 4
  store i32 %a, i32* %a1, align 4
  %b2 = alloca i32, align 4
  store i32 %b, i32* %b2, align 4
  %a3 = load i32, i32* %a1, align 4
  %b4 = load i32, i32* %b2, align 4
  %tmpadd = add i32 %a3, %b4
  ret i32 %tmpadd
}
