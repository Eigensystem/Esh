#include <iostream>
#include <unistd.h>
#include <sys/param.h>
#include "InnerCommand.hh"
#include "EshException.hh"

using namespace std;

InnerCommand::InnerCommand(InnerCmdManager &cmd_mgr) {
  cmd_mgr.register_inner(_cmd_name, *this);
}

int CD::work(const vector<string> &argu) {
  int rc;
  if (argu.size() > 2) {
    cerr << "Esh: cd: too many arguments" << endl;
    return -1;
  }
  else if(argu.size() == 1) {
    rc = chdir(getenv("HOME"));
  }
  else {
    string home_dir = getenv("HOME");
    string path = argu[1];
    while(path.find("~") != string::npos) {
      int idx = path.find("~");
      path = path.substr(0, idx) + home_dir + path.substr(idx+1);
    }
    rc = chdir(path.c_str());
  }
  if (rc < 0) {
    try {
      throw ExecuteException(ExceptionType::CommandFailed, errno, argu[0]);
    }
    catch(const EshException& e) {
      cerr << e.what() << endl << e.errormsg() << endl;
    }
    return -1;
  }
  return 0;
}

int PWD::work(const vector<string> &argu) {
  char buf[MAXPATHLEN];
  string workdir = getcwd(buf, MAXPATHLEN);
}