#pragma once

#include <vector>
#include <string>
#include "CommandManager.hh"

class InnerCommand {
  string _cmd_name;

public:
  InnerCommand(CommandManager &cmd_mgr);
  virtual size_t work() = 0;
};

class CD : InnerCommand {
public:
  virtual size_t work(vector<string> &argu);
};

// class 