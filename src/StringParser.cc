#include "StringParser.hh"
#include "EshException.hh"

void CommandFlags::reset() {
  _inpipe = 0;
  _outpipe = 0;
  _background = 0;
  _prev_success = 0;
  return;
}

bool StringParser::parse_str(string s) {
  size_t pos = s.find_first_not_of(" ");
  size_t argu_start = 0, quote_start = 0;
  // if not command to execute, exit to main loop
  if (pos == string::npos) {
    return false;
  }
  _cnt = 0;
  vector<string> comm_argu;
  CommandFlags flags;
  // travelsal the string
  while(pos < s.size()) {
    switch (s.at(pos))
    {
      case ' ':
        pos = s.find_first_not_of(" ", pos);
        argu_start = pos;
        break;
      case '\"':
        quote_start = pos;
        pos = s.find_first_of('\"', pos+1);
        while (s.at(pos-1) == '\\' && pos != string::npos) {
          pos = s.find_first_of('\"', pos+1);
        }
        if (pos == string::npos) {
          try {
            throw CommandInException(ExceptionType::StringParserError);
          } catch (CommandInException &e) {
            cerr << "Can not find subsequent quote mark of mark \'\"\' at :" 
                << to_string(quote_start) << endl;
            throw;
          }
        }
        comm_argu.push_back(s.substr(quote_start+1, pos - quote_start - 1));
        ++pos;
        break;
      case '\'':
        quote_start = pos;
        pos = s.find_first_of('\'', pos+1);
        while (s.at(pos-1) == '\\' && pos != string::npos) {
          pos = s.find_first_of('\'', pos+1);
        }
        if (pos == string::npos) {
          try {
            throw CommandInException(ExceptionType::StringParserError);
          } catch (CommandInException &e) {
            cerr << "Can not find subsequent quote mark of mark \'\'\' at :" 
                << to_string(quote_start) << endl;
            throw;
          }
        }
        comm_argu.push_back(s.substr(quote_start+1, pos - quote_start - 1));
        ++pos;
        break;
      case ';':
        comm_argu.push_back(s.substr(argu_start, pos - argu_start));
        ++_cnt;
        _arguments.push_back(comm_argu);
        comm_argu.clear();
        _command_flags.push_back(flags);
        flags.reset();
        if (pos + 1 < s.size()) {
          ++pos;
        }
        break;
      case '|':
        comm_argu.push_back(s.substr(argu_start, pos - argu_start));
        ++_cnt;
        _arguments.push_back(comm_argu);
        comm_argu.clear();
        flags._outpipe = 1;
        _command_flags.push_back(flags);
        flags.reset();
        flags._inpipe = 1;
        //TODO: pipe prompt sign (in else)
        if (pos + 1 < s.size()) {
          ++pos;
        }
        break;
      case '&':
        comm_argu.push_back(s.substr(argu_start, pos - argu_start));
        if (pos + 1 < s.size() && s.at(pos+1) == '&') {
          ++_cnt;
          _arguments.push_back(comm_argu);
          comm_argu.clear();
          _command_flags.push_back(flags);
          flags.reset();
          flags._prev_success = 1;
          //TODO: cmdand prompt sign (in else)
          if (pos + 2 < s.size()) {
            pos += 2;
          }
        }
        else {
          ++_cnt;
          _arguments.push_back(comm_argu);
          comm_argu.clear();
          flags._background = 1;
          _command_flags.push_back(flags);
          flags.reset();
          if (pos + 1 < s.size()) {
            ++pos;
          }
        }
        break;
      default:
        if (pos + 1 >= s.size() || s.at(pos+1) == ' ') {
          comm_argu.push_back(s.substr(argu_start, pos - argu_start + 1));
        }
        ++pos;
        break;
    }
  }
  if (!comm_argu.empty()) {
    _arguments.push_back(comm_argu);
    _command_flags.push_back(flags);
  }
  return true;
}


StringParser::StringParser(string command) {
  parse_str(command);
}

pair<vector<string>&, CommandFlags&>
StringParser::operator[](size_t idx)
{
  return pair<vector<string>&, CommandFlags&>(_arguments[idx], _command_flags[idx]);
}

pair<const vector<string>&, const CommandFlags&> 
StringParser::operator[](size_t idx) const
{
  return pair<const vector<string>&, const CommandFlags&>(_arguments[idx], _command_flags[idx]);
}