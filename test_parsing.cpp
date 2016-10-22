#include "parsing.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>

int main(){
  std::ifstream infile("foo.txt");
  std::stringstream buffer;
  buffer << infile.rdbuf();
  std::string buffer_str = buffer.str();
  // std::cout << buffer_str << std::endl;
  std::queue<Token*>* tokens = lex(buffer_str);
  if (tokens != NULL) {
    std::cout << "Lexing: DONE" << std::endl;
    std::cout << tokens->size() << " Tokens" << std::endl;
  } else {
    std::cout << "Lexing: NULL" << std::endl;
  }
  Tree * parsed = parse(tokens);
  if (parsed != NULL){
    std::cout << "Parsing: " << std::endl << *parsed << std::endl;
  } else {
    std::cout << "Parsing: NULL" << std::endl;
  }
}
