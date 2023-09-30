#ifndef AURUM_CUSTOM_EXCEPTIONS_H
#define AURUM_CUSTOM_EXCEPTIONS_H

#include <exception>
#include <string>

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

class QueueFinalizedException: virtual public BaseException{
public:
    QueueFinalizedException();    
};

class QueueNotFinalizedException: virtual public BaseException{
public:
    QueueNotFinalizedException();    
};

class UnavailableAlgorithmException: virtual public BaseException{
public:
    UnavailableAlgorithmException(const std::string&);
};

class ProcessDoesNotExistException: virtual public BaseException{
public:
    ProcessDoesNotExistException();    
};

class ExecutionCompletedException: virtual public BaseException{
public:
    ExecutionCompletedException();    
};

#endif