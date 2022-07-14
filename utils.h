#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

class Process {
  public:

  int process_id;
  int parent_id;

  string process_path;

};


// split strings into a vector of substrings
vector<string> split(string s, string delimiter) {
  vector<string> v;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    v.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  v.push_back(s);
  return v;
}
