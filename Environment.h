#ifndef Environment_h
#define Environment_h


#include <map>
#include <memory>
#include <string>


#include "./Logger.h"
#include "llvm/IR/Value.h"

//extend shared from this to enable returning shared pointers
class Environment : public std::enable_shared_from_this<Environment>{
    public:

    Environment(std::map<std::string, llvm::Value*> record, 
                std::shared_ptr<Environment> parent) : record_(record), parent_(parent) {}


    llvm::Value* define(const std::string& name, llvm::Value* value){
        record_[name] = value;
        return value;
    }

    llvm::Value* lookup(const std::string& name){
        //resolve traverse the environment chain
        return resolve(name)->record_[name];
    }


    private:

    //return specific environment in which the variable exists

    std::shared_ptr<Environment> resolve(const std::string& name){
        if(record_.count(name)!=0){
            return shared_from_this();
        }

        //global env that does not have any parent
        if (parent_ == nullptr){
            DIE << "Variable  \"" << name << "\" is not defined.";
        }

        return parent_ -> resolve(name);
    }

    std::map<std::string, llvm::Value*> record_;

    std::shared_ptr<Environment> parent_;


};

#endif