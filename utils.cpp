#include "utils.h"

#include <string>
#include <vector>
#include <sstream>

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss;
  ss.str(s);  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
}


std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

std::string indent(std::string s, std::string indentation){
  std::istringstream iss(s);
  std::string result;
  for (std::string line; std::getline(iss, line); ){
    result += indentation + line + "\n";
  }
  result.pop_back();
  return result;
}
