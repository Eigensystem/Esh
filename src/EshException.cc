#include "EshException.hh"

string& operator+=(string &s, const ExceptionType &etype) {
  switch (etype) {
    case ExceptionType::StringParserError:
      s += "StringParseError";
      break;
    default:
      break;
  }
  return s;
}

const char* CommandInException::what() const throw() {
  string msg = "Exception Stage: command input\n";
  msg += "Exception Type: ";
  msg += type;
  msg += "\n";
  return msg.c_str();
}