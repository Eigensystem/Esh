#pragma once

#include <unordered_map>
#include <string>
#include <optional>
#include "InnerCommand.hh"

using namespace std;

class CommandManager {
  unordered_map<string, InnerCommand&> _innercmd;

public:
  CommandManager() = default;
  // the first thing inner cmd will do is register itself to _innercmd
  void register_inner(string cmd, InnerCommand& cmd_instance);
  std::optional<InnerCommand&> get_inner(string cmd);
};