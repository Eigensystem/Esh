#include "CommandManager.hh"

void CommandManager::register_inner(string cmd, InnerCommand& cmd_instance) {
  if (_innercmd.find(cmd) == _innercmd.end()) {
    _innercmd[cmd] = cmd_instance;
  }
}

std::optional<InnerCommand&> CommandManager::get_inner(string cmd) {
  if (_innercmd.find(cmd) == _innercmd.end()) return nullopt;
  else return _innercmd.find(cmd)->second;
}