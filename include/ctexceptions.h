#ifndef _SCHV_CUSTOM_EXCEPTIONS_H
#define _SCHV_CUSTOM_EXCEPTIONS_H 1

#include<exception>
#include<string>

class BaseException:virtual public std::exception{
protected:
    int errorNumber;
    std::string errorMessage;
public:
    BaseException(const std::string&, const int);
    virtual const char* what() const throw();
    virtual int getErrorNumber();
};

class FatalException: virtual public BaseException{
public:
    FatalException();
};

class OutOfBoundsException: virtual public BaseException{
public:
    OutOfBoundsException();
};

class InvalidInputException: virtual public BaseException{
public:
    InvalidInputException();    
};

class EndOfFileException: virtual public BaseException{
public:
    EndOfFileException();    
};

class FileException: virtual public BaseException{
public:
    FileException(std::string);
};

#endif