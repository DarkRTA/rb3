#include "qresult.hpp"

Quazal::qResult::qResult(){
    i1 = 0x80010001;
    c = "Result.cpp";
    i2 = 0x14;
}

Quazal::qResult::qResult(const int& i){
    i1 = i;
    c = "Result.cpp";
    i2 = 0x1B;
}

bool Quazal::qResult::Equals(const int& i) const {
    return (i1 == i);
}

bool Quazal::qResult::Equals(const bool& b) const {
    return ((i1 >= 0) == b);
}

Quazal::qResult::operator bool() const {
    return (i1 >= 0);
}

Quazal::qResult* Quazal::qResult::operator=(const int& i){
    i1 = i;
    c = "Result.cpp";
    i2 = 0x59;
    return this;
}

Quazal::qResult* Quazal::qResult::operator=(const Quazal::qResult& res){
    i1 = res.i1;
    c = res.c;
    i2 = res.i2;
    return this;
}

void Quazal::qResult::Trace(unsigned int) const {

}

const char* UnusedQResultReturnCodeFxn(){
    return "ReturnCode ";
}

const char* UnusedQResultOriginFxn(){
    return " (origin ";
}

const char* UnusedQResultLineFxn(){
    return ", line ";
}

const char* UnusedQResultEndParenFxn(){
    return ")";
}