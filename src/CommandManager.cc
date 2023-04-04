#include "CommandManager.hh"

void InnerCmdManager::register_inner(string cmd, InnerCommand& cmd_instance) {
  if (_innercmd.find(cmd) == _innercmd.end()) {
    _innercmd[cmd] = cmd_instance;
  }
}

std::optional<InnerCommand&> InnerCmdManager::get_inner(string cmd) {
  if (_innercmd.find(cmd) == _innercmd.end()) return nullopt;
  else return _innercmd.find(cmd)->second;
}


void CommandFlags::reset() {
  _inpipe = 0;
  _outpipe = 0;
  _background = 0;
  _prev_success = 0;
  return;
}


pair<vector<string>&, CommandFlags&>
CommandManager::operator[](size_t idx)
{
  return pair<vector<string>&, CommandFlags&>(_arguments[idx], _command_flags[idx]);
}

pair<const vector<string>&, const CommandFlags&> 
CommandManager::operator[](size_t idx) const
{
  return pair<const vector<string>&, const CommandFlags&>(_arguments[idx], _command_flags[idx]);
}