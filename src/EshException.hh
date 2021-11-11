#pragma once

#include <iostream>
#include <exception>

using namespace std;

enum class ExceptionType {
  StringParserError,
};

string& operator+=(string &s, const ExceptionType &etype);

class EshException: public exception {
protected:
  ExceptionType type;
public:
  EshException(const ExceptionType t) : type(t), exception() {}
  virtual const char* what() const throw() = 0;
};


class CommandInException: public EshException {
public:
  CommandInException(const ExceptionType t) : EshException(t) {}
  virtual const char* what() const throw();
};

// class ExecuteException: public EshException {
//   public:
//     ExecuteException(const ExceptionType t) : EshException(t) {}
// };

// class ResultOutException: public EshException {
//   public:
//     ResultOutException(const ExceptionType t) : EshException(t) {}

// };

// class ToCommandIn: public exception {
//   virtual const char* what() const throw() {}
// };