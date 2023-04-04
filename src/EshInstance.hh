#pragma once

#include "StringParser.hh"
#include "EshException.hh"
#include "CommandManager.hh"

class EshInstance {
  CommandManager _cmd_mgr;
  StringParser _cmd_parser;

  EshInstance();
};