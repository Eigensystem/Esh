#pragma once

#include <vector>
#include <string>
#include <bitset>
#include <utility>

using namespace std;

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

class StringParser {
  vector<vector<string>> _arguments;
  vector<CommandFlags> _command_flags;
public:
  size_t _cnt;
  string _in_file;
  string _out_file;

  StringParser() = delete;
  StringParser(string command);

  bool parse_str(string s);

  pair<vector<string>&, CommandFlags&> operator[](size_t idx);

  pair<const vector<string>&, const CommandFlags&> operator[](size_t idx) const;
};