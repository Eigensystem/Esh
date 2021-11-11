#pragma once

#include "StringParser.hh"
#include "EshException.hh"
#include "CommandManager.hh"

class EshInstance {
  CommandManager cmd_mgr;
  StringParser cmd_parser;

  EshInstance();
};