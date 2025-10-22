#ifndef EVA_LLVM_H 
#define EVA_LLVM_H


#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "./parser/EvaParser.h"

using syntax::EvaParser;

class EvaLLVM {

    public:
        EvaLLVM() : parser(std::make_unique<EvaParser>()){  
            moduleInit(); // Initialize pointers
            setupExternFunctions();
        }


    void exec(const std::string& program){
        // 1.parse the program
        auto ast = parser -> parse(program);

        //2. Compile to LLVM IR
        compile(ast);

        module -> print(llvm::outs(),nullptr);


        //3.Save module IR to file
        saveModuleToFile("./out.ll");   

    }
    private:


        void compile(const Exp& ast){
            //1. create main function
            fn = createFunction("main", llvm::FunctionType::get(builder->getInt32Ty(), false));

            CreateGlobalVar("VERSION", builder->getInt32(42));

            //2. compile main bidy
            gen(ast);

            builder -> CreateRet(builder->getInt32(0));
        }


        llvm::Value* gen(const Exp& exp){

            switch(exp.type){
                case ExpType::NUMBER:
                    return builder -> getInt32(exp.number);

                case ExpType::STRING:
                    return builder -> CreateGlobalStringPtr("Hello, world!\n");

                case ExpType::SYMBOL:
                    if (exp.string == "true" || exp.string == "false"){
                        return builder -> getInt1(exp.string== "true" ? true : false);
                    }
                    else{

                        return module->getNamedGlobal(exp.string)->getInitializer();

                    }


                case ExpType::LIST:
                    auto tag = exp.list[0];
                    if (tag.type == ExpType::SYMBOL){
                        auto op = tag.string;
                        if (op == "var"){
                            auto varName = exp.list[1].string;
                            auto init = gen(exp.list[2]);

                            return CreateGlobalVar(varName, (llvm::Constant *) init);
                        }
                        else if(op == "printf"){

                            auto printfFn = module->getFunction("printf");
                            std::vector<llvm::Value*> args{};
                            for(auto i =1; i < exp.list.size(); i++){
                                args.push_back(gen(exp.list[i]));
                            }
                            return builder->CreateCall(printfFn,args);

                            }
                    }
                }
            }
            //for number 
            //return builder -> getInt32(42);

            //for strings
        
        
        llvm::GlobalVariable* CreateGlobalVar(const std::string& name, llvm::Constant* init){

            module->getOrInsertGlobal(name, init->getType());
            auto variable = module -> getNamedGlobal(name);
            variable->setAlignment(llvm::MaybeAlign(4));
            variable->setConstant(false);
            variable->setInitializer(init);
            return variable;    

        }

        void setupExternFunctions(){
            //i8*
            auto bytePtrTy = builder->getInt8Ty()->getPointerTo();

            module->getOrInsertFunction("printf", llvm::FunctionType::get(builder->getInt32Ty(), bytePtrTy, true));

        }

        llvm::Function* createFunction(const std::string& fnName, llvm::FunctionType* fnType){
            
            auto fn = module->getFunction(fnName);
            if (fn == nullptr){
                fn = createFunctionProto(fnName, fnType);
            }
            createFunctionBlock(fn);
            return fn;  

            }

        llvm::Function* createFunctionProto(const std::string& fnName, llvm::FunctionType* fnType){

            auto fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, fnName, *module);
            verifyFunction(*fn);
            return fn;
        }

        void createFunctionBlock(llvm::Function* fn){
            auto entry = createBB("entry", fn);
            builder->SetInsertPoint(entry);
        }

        llvm::BasicBlock* createBB(std::string name, llvm::Function* fn = nullptr){
            return llvm::BasicBlock::Create(*ctx, name, fn);
        }

        void saveModuleToFile(const std::string& fileName){
            std::error_code errorCode;
            llvm::raw_fd_ostream outLL(fileName, errorCode);
            module -> print(outLL,nullptr);
        }

        void moduleInit(){

            ctx = std::make_unique<llvm::LLVMContext>();
            module = std::make_unique<llvm::Module>("EvaLLVM", *ctx);
            builder = std::make_unique<llvm::IRBuilder<>>(*ctx);


        }

        std::unique_ptr<llvm::LLVMContext> ctx;
        std::unique_ptr<llvm::Module> module;
        std::unique_ptr<llvm::IRBuilder<>> builder;

        std::unique_ptr<EvaParser> parser;

        llvm::Function* fn; 


};

#endif
