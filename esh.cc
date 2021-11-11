#include <string>
#include <iostream>
#include "StringParser.hh"
#include "EshException.hh"

int main() {
  string command("ls \"/bin\" -la ; ls          | hi & 'no' what is tha ");
  StringParser test(command);
  for (int i = 0; i < test._cnt; ++i) {
    for (auto j: test[i].first) {
      cout << j << " ";
    }
    cout << "\nflags:" << test[i].second._inpipe << test[i].second._outpipe
        << test[i].second._background << test[i].second._prev_success << endl;
  }
  return 0;
}