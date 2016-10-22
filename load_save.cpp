#include "load_save.h"

#include "task_manager.h"
#include "project.h"
#include "task.h"
#include "parsing.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>

using std::string;
using std::ofstream;
using std::unordered_map;
using std::vector;

Saver::Saver(TaskManager * task_manager, string fName){
  this->task_manager = task_manager;
  this->fName = fName;
}

void Saver::setTaskManager(TaskManager* task_manager){
  this->task_manager = task_manager;
}

void Saver::setFileName(string fName){
  this->fName = fName;
}

void Saver::save(){
  ofstream ofs;
  remove(fName.c_str());
  ofs.open (this->fName, std::ofstream::out | std::ofstream::app);
  ofs << task_manager->getJSON();
  ofs.close();
}

Loader::Loader(TaskManager* task_manager, string fName){
  this->task_manager = task_manager;
  this->fName = fName;
}

void Loader::setTaskManager(TaskManager* task_manager){
  this->task_manager = task_manager;
}

void Loader::setFileName(string fName){
  this->fName = fName;
}

TaskManager* Loader::getTaskManager() const{
  return this->task_manager;
}

Task* Loader::taskFromTree(Tree* tree) const{
  if (tree->getContent() != "object"){
    return NULL;
  }
  string title, details;
  for (Tree* child : *tree->getChildren()){
    if (child->getContent() == "title"){
      title = child->getChildren()->front()->getContent();
    } else if (child->getContent() == "details"){
      details = child->getChildren()->front()->getContent();
    } else {
      return NULL;
    }
  }
  if (title != ""){
    return new Task(title, details);
  } else {
    return NULL;
  }
}

Project* Loader::projectFromTree(Tree* tree) const{
  if (tree->getContent() != "object"){
    return NULL;
  }
  string name;
  vector<Task*> tasks;
  Task* temp;
  for (Tree* child : *tree->getChildren()){
    if (child->getContent() == "name"){
      name = child->getChildren()->front()->getContent();
    } else if (child->getContent() == "tasks"){
      for (Tree* taskTree : *child->getChildren()){
	temp = taskFromTree(taskTree);
	if (temp != NULL){
	  tasks.push_back(temp);
	}
      }
    } else {
      return NULL;
    }
  }
  Project* return_proj = new Project(name);
  for (Task* t : tasks){
    return_proj->addTask(t);
  }
  return return_proj;
}

TaskManager* Loader::taskManagerFromTree(Tree* tree) const {
  string save_file;
  Task* curr_task;
  Project* curr_proj;
  vector<Project*> projects;

  Project* temp;

  for (Tree* child : *tree->getChildren()){
    if (child->getContent() == "save_file"){
      save_file = child->getContent();
    } else if (child->getContent() == "current_project"){
      curr_proj = projectFromTree(child->getChildren()->front());
    } else if (child->getContent() == "current_task"){
      curr_task = taskFromTree(child->getChildren()->front());
    } else if (child->getContent() == "projects"){
      for (Tree* projTree : *child->getChildren()){
	temp = projectFromTree(projTree);
	if (temp != NULL){
	  projects.push_back(temp);
	}
      }
    } else {
      return NULL;
    }
  }
  if (curr_task != NULL){
    for (Project* p : projects){
      for (Task* t : p->getTasks()){
	if (t->getTitle() == curr_task->getTitle() && t->getDetails() == curr_task->getDetails()){
	  curr_task = t;
	  break;
	}
      }
    }
  }
  if (curr_proj != NULL){
    for (Project* p : projects){
      if (p->getName() == curr_proj->getName()){
	curr_proj = p;
	break;
      }
    }
  }
  TaskManager* returnTM = new TaskManager(save_file,std::cout, std::cin);
  returnTM->setCurrProj(curr_proj);
  returnTM->setCurrTask(curr_task);
  for (Project* p : projects){
    returnTM->addProj(p);
  }
  return returnTM;
}

int Loader::load(){
  std::ifstream infile(fName);
  std::stringstream buffer;
  buffer << infile.rdbuf();
  std::string buffer_str = buffer.str();
  std::cout << "BUFFER " << buffer_str << std::endl;
  std::queue<Token*>* tokens = lex(buffer_str);
  std::cout << "TOKENIZED " << tokens->size() << std::endl;;
  Tree * parsed = parse(tokens);
  std::cout << "PARSED" << std::endl;;
  TaskManager* tm;
  if (parsed != NULL){
    tm = taskManagerFromTree(parsed);
  } else{
    tm = NULL;
  }
  this->task_manager = tm;
  if (tm != NULL){
    return 0;
  } else {
    return 1;
  }
}
