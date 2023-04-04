#pragma once

#include <vector>
#include <string>
#include "CommandManager.hh"

class InnerCommand {
  string _cmd_name;

public:
  InnerCommand(InnerCmdManager &cmd_mgr);
  virtual int work(const vector<string> &argu) = 0;
};

class CD : InnerCommand {
  string _cmd_name = "cd";
public:
  using InnerCommand::InnerCommand;
  virtual int work(const vector<string> &argu) override;
};

class PWD : InnerCommand {
  string _cmd_name = "pwd";
public:
  using InnerCommand::InnerCommand;
  virtual int work(const vector<string> &argu) override;
};

class ECHO : InnerCommand {
  string _cmd_name = "echo";
public:
  using InnerCommand::InnerCommand;
  virtual int work(const vector<string> &argu) override;
};