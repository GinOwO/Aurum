#include "ctexceptions.h"

#include<exception>
#include<string>

BaseException::BaseException(const std::string& _err_msg, const int _err_num){
    errorMessage=_err_msg;
    errorNumber=_err_num;
}
const char* BaseException::what() const throw(){
    return this->errorMessage.c_str();
}

int BaseException::getErrorNumber(){
    return errorNumber;
}

FatalException::FatalException(
    ):BaseException("Fatal Exception has Occurred. Please Restart",1){};

OutOfBoundsException::OutOfBoundsException(
    ):BaseException("OutOfBoundsException Raised",10){}

InvalidInputException::InvalidInputException(
    ):BaseException("InvalidInputException Raised", 20) {}