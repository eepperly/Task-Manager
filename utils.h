#ifndef _UTILS_H
#define _UTILS_H

#include <vector>
#include <string>

void split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
std::string indent(std::string s, std::string indentation);

#endif // _UTILS_H
