#include "parsing.h"

#include "utils.h"

#include <string>
using std::string;

#include <queue>
using std::queue;

#include <list>
using std::list;

#include <stack>
using std::stack;

#include <iostream>
using std::ostream;

#include <sstream>
using std::ostringstream;

// Token stuff

const string null_string = "null"; // null literal

Token* lbrace = new Token(t_lbrace, "{");
Token* rbrace = new Token(t_rbrace, "}");
Token* lbrack = new Token(t_lbrack, "[");
Token* rbrack = new Token(t_rbrack, "]");
Token* comma  = new Token(t_comma, ",");
Token* null   = new Token(t_null, "null");
Token* colon  = new Token(t_colon, ":");
Token* ptag   = new Token(p_tag, "tag");
Token* pvalue = new Token(p_value, "value");
Token* parray = new Token(p_array, "array");

Token::Token(TokenType type, std::string content){
  this->type = type;
  this->content = content;
}

TokenType Token::getType() const{
  return this->type;
}

string Token::getContent() const{
  return this->content;
}

// Lexing

queue<Token*> * lex(string input){
  string currStr = "";
  bool inString = false;
  bool inNull = false;
  queue<Token*>* tokens = new queue<Token*>;
  for (char c : input){
        if (inString){
      if (c != '"'){
	currStr += c;
      } else{
	Token* t = new Token(t_string, currStr);
	tokens->push( t );
	currStr = "";
	inString = false;
      }
    } else if (inNull){
      if ( c == null_string.at(currStr.length()) ){
	// c is next character in "null"
	currStr += c;
	if ( currStr == "null" ){
	  tokens->push(null);
	  inNull = false;
	  currStr = "";
	}
      } else {
	return NULL; // Error
      }
    } else {
      if ( c == '{' ){
	tokens->push(lbrace);
      } else if ( c == '}' ){
	tokens->push(rbrace);
      } else if ( c == '[' ){
	tokens->push(lbrack);
      } else if ( c == ']' ){
	tokens->push(rbrack);
      } else if ( c == ',' ){
	tokens->push(comma);
      } else if ( c == ':' ){
	tokens->push(colon);
      } else if ( c == '"' ){
	inString = true;
	currStr = "";
      } else if ( c == 'n' ){
	inNull = true;
	currStr = "";
      } else if ( c!=' ' && c!='\n' && c!='\t' ){
	return NULL;
      }
    }
  }
  return tokens;
}

// Parsing

Tree * parse(std::queue<Token*>* tokens){
  stack<Token*> tokenStack;
  if (tokens == NULL || tokens->empty() || tokens->front()->getType() != t_lbrace){
    return NULL;
  }

  tokens->pop();
  tokenStack.push(lbrace);
  Tree* parse_tree = new Tree("object");
  Tree* parse_tree_loc = parse_tree;
  Token* token;
  TokenType top_type;

  int flag;

  while (true){
    if (tokens->empty()){
      break;
    }

    token = tokens->front();
    tokens->pop();
    top_type = tokenStack.top()->getType();

    if (token->getType() == t_string){
      // std::cout << "STRING" << std::endl;
      if (top_type == t_lbrace || top_type == t_comma){
	// std::cout << "  TAG" << std::endl;
	parse_tree_loc = parse_tree_loc->addChild(token->getContent());
	tokenStack.push(ptag);
      } else if (top_type == t_colon){
	// std::cout << "  VALUE" << std::endl;
	parse_tree_loc = parse_tree_loc->addChild(token->getContent());
	tokenStack.push(pvalue);
      } else {
	return NULL; // Error
      }
    } else if (token->getType() == t_num || token->getType() == t_null){
      // std::cout << "NUM OR NULL" << std::endl;
      if (top_type == t_colon){
	parse_tree_loc = parse_tree_loc->addChild(token->getContent());
	tokenStack.push(pvalue);
      } else {
	return NULL; // Error
      }
    } else if (token->getType() == t_colon){
      // std::cout << "COLON" << std::endl;
      if (top_type == p_tag){
	tokenStack.push(colon);
      } else {
	return NULL; // Error
      }
    } else if (token->getType() == t_lbrace){
      // std::cout << "LBRACE" << std::endl;
      if (top_type == t_colon || top_type == t_lbrack){
	parse_tree_loc = parse_tree_loc->addChild("object");
	tokenStack.push(lbrace);
      } else {
	return NULL; // Error
      }
    } else if (token->getType() == t_rbrace){
      // std::cout << "RBRACE" << std::endl;
      flag = 1;
      flag *= pop_assert_type(&tokenStack, p_value); // value
      flag *= pop_assert_type(&tokenStack, t_colon); // colon
      flag *= pop_assert_type(&tokenStack, p_tag); // tag
      flag *= pop_assert_type(&tokenStack, t_lbrace); // lbrace
      if (flag == 0) { return NULL; }
      
      parse_tree_loc = parse_tree_loc->getParent()->getParent();
      if (!tokenStack.empty()){
	top_type = tokenStack.top()->getType();
	if (top_type == t_colon){
	  tokenStack.push(pvalue);
	  // parse_tree_loc = parse_tree_loc->getParent();
	} else if (top_type == t_lbrack){
	  tokenStack.push(parray);
	}
      }
    } else if (token->getType() == t_lbrack){
      // std::cout << "LBRACK" << std::endl;
      if (top_type == t_colon){
	tokenStack.push(lbrack);
      } else {
	return NULL; // Error
      }
    } else if (token->getType() == t_rbrack){
      // std::cout << "RBRACK" << std::endl;
      flag = 1;
      if (top_type == p_array) {
	flag *= pop_assert_type(&tokenStack, p_array);
      }
      flag *= pop_assert_type(&tokenStack, t_lbrack); // lbrace
      if (flag == 0) { return NULL; }
      
      tokenStack.push(pvalue);
    } else if (token->getType() == t_comma){
      // std::cout << "COMMA" << std::endl;
      
      if (top_type == p_value){
	flag = 1;
	flag *= pop_assert_type(&tokenStack, p_value); // value
	flag *= pop_assert_type(&tokenStack, t_colon); // colon
	flag *= pop_assert_type(&tokenStack, p_tag); // tag
	if (flag == 0) { return NULL; }
	
	// go up two levels in tree
	parse_tree_loc = parse_tree_loc->getParent()->getParent();
      } else if (top_type == p_array){
	flag = pop_assert_type(&tokenStack, p_array); // value
	if (flag == 0) { return NULL; }
	
	// go up one level in tree
	parse_tree_loc = parse_tree_loc->getParent();
      } else {
	return NULL; // Error
      } 
    } 
  }
  return parse_tree;
}

int pop_assert_type(stack<Token*>* my_stack, TokenType type){
  if (my_stack->top()->getType() == type){
    my_stack->pop();
    return 1;
  } else {
    return 0;
  } 
}

// Tree

Tree::Tree(string content){
  this->content = content;
  this->parent = NULL;
}

Tree::~Tree(){
  for (Tree* child : children){
    delete child;
  }
  delete &children;
  delete this;
}

string Tree::getContent() const{
  return this->content;
}

list<Tree*> Tree::getChildren() const{
  return this->children;
}

Tree* Tree::getParent() const{
  return this->parent;
}

void Tree::setParent(Tree* parent){
  this->parent = parent;
}

Tree* Tree::addChild(Tree* newChild){
  children.push_back(newChild);
  newChild->setParent(this);
  return newChild;
}

Tree* Tree::addChild(string child){
  Tree* t = new Tree(child);
  return this->addChild(t);
}

ostream & operator <<(ostream & os, Tree & tree){
  os << tree.getContent();
  ostringstream oss;
  for (Tree* child : tree.getChildren()){
    oss << std::endl << *child;
    os << indent(oss.str(), "  ");
    oss.str("");
  }
  return os;
}
