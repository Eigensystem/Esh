#include "InnerCommand.hh"

InnerCommand::InnerCommand(CommandManager &cmd_mgr) {
  cmd_mgr.register_inner(_cmd_name, *this);
}

size_t CD::work(vector<string> &argu) {
  
}