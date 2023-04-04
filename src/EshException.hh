#pragma once

#include <iostream>
#include <exception>

using namespace std;

enum class ExceptionType {
  StringParserError,
  CommandFailed,
};
string& operator+=(string &s, const ExceptionType &etype);

class EshException: public exception {
protected:
  ExceptionType _type;
public:
  EshException(const ExceptionType t) : _type(t), exception() {}
  virtual const char* what() const throw() = 0;
  virtual const string errormsg() const noexcept = 0;
};


class CommandInException: public EshException {
public:
  CommandInException() = delete;
  CommandInException(const ExceptionType t) : EshException(t) {}
  virtual const char* what() const throw() override;
  virtual const string errormsg() const noexcept override;
};

class ExecuteException: public EshException {
  int _errno;
  string _cmd;
public:
  ExecuteException() = delete;
  ExecuteException(const ExceptionType t, const int n, string cmd)
    : EshException(t), _errno(n), _cmd(cmd) {}
  virtual const char* what() const throw() override;
  virtual const string errormsg() const noexcept override;
};


// class ResultOutException: public EshException {
//   public:
//     ResultOutException(const ExceptionType t) : EshException(t) {}

// };
