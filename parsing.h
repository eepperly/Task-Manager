#ifndef _PARSING_H
#define _PARSING_H

#include <string>
#include <queue>
#include <stack>
#include <list>
#include <iostream>

enum TokenType { t_lbrace, t_rbrace, t_lbrack, t_rbrack, t_comma,
		 t_string, t_num, t_null, t_colon, p_tag, p_value,
		 p_array};

class Token{
 public:
  Token(TokenType type, std::string content);
  TokenType getType() const;
  std::string getContent() const;
 private:
  TokenType type;
  std::string content;
};

std::queue<Token*> * lex(std::string input);
class Tree;
Tree * parse(std::queue<Token*> * tokens);
int pop_assert_type(std::stack<Token*>* my_stack, TokenType type);

class Tree{
 public:
  Tree(std::string content);
  ~Tree();
  std::string getContent() const;
  std::list<Tree*> getChildren() const;
  Tree* getParent() const;
  void setParent(Tree* parent);
  Tree* addChild(Tree* newChild);
  Tree* addChild(std::string child);
 private:
  Tree* parent;
  std::string content;
  std::list<Tree*> children;
};

std::ostream & operator <<(std::ostream & os, Tree & tree);

#endif // _PARSING_H
