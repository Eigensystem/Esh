#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <optional>
#include "InnerCommand.hh"

using namespace std;

class InnerCmdManager {
  unordered_map<string, InnerCommand&> _innercmd;

public:
  // InnerCmdManager() = default;
  void register_inner(string cmd, InnerCommand& cmd_instance);
  std::optional<InnerCommand&> get_inner(string cmd);
};


struct CommandFlags {
  bool _inpipe = 0;
  bool _outpipe = 0;
  bool _background = 0;
  bool _prev_success = 0;

  CommandFlags() = default;
  CommandFlags(bool inpipe, bool outpipe, bool background, bool prev_success)
    : _inpipe(inpipe), _outpipe(outpipe), _background(background), 
      _prev_success(prev_success) {}

  void reset();
};


class CommandManager {
  friend class StringParser;

  InnerCmdManager _inner_mgr;
  vector<vector<string>> _arguments;
  vector<CommandFlags> _command_flags;
  size_t _cnt;
  string _in_file;
  string _out_file;

public:
  CommandManager() : _inner_mgr() {}
  pair<vector<string>&, CommandFlags&> operator[](size_t idx);
  pair<const vector<string>&, const CommandFlags&> operator[](size_t idx) const;
};