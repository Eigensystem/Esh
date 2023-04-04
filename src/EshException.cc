// #include <unistd.h>
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
  return "Exception Stage: command input";
}

const string CommandInException::errormsg() const noexcept {
  string type_msg = "Exception Type: ";
  type_msg += _type;
  return type_msg;
}

const char* ExecuteException::what() const throw() {
  return "Exception Stage: Execution";
}

const string ExecuteException::errormsg() const noexcept{
  string type_msg = "Exception Type: ";
  type_msg += _type;
  string cmd_msg = _cmd + ": ";
  switch (_errno)
  {
  case EACCES:
    cmd_msg += "Permission denide";
    break;
  case ELOOP:
    cmd_msg += "Loop exists in symbolic links";
  case ENAMETOOLONG:
    cmd_msg += "Too long pathname";
  case ENOENT:
    cmd_msg += "No such file or directory";
  case ENOTDIR:
    cmd_msg += "Not a directory";
  default:
    break;
  }
  return type_msg + "\n" + cmd_msg;
}