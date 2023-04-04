#pragma once

#include <string>
#include "CommandManager.hh"

using namespace std;


class StringParser {
public:
  StringParser() = delete;
  StringParser(string command, CommandManager& mgr);

  bool parse_str(string s, CommandManager& mgr);
};