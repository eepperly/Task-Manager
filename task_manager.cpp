#include <iostream>
#include <string>

#include "utils.h"
#include "project.h"
#include "task.h"
#include "task_manager.h"

using std::ostream;
using std::istream;
using std::string;

TaskManager::TaskManager(ostream & os, istream & is) : os(os), is(is) {
  // this->os = os;
  // this->is = is;
  this->currProj = NULL;
  this->currTask = NULL;

  this->navCmds = new stack<string>();
  this->projects = new vector<Project*>();
}

TaskManager::~TaskManager(){
  for (Project* p : *projects){
    delete p;
  }
  delete projects;
  delete navCmds;
}

Project* TaskManager::create_project(){
  string projectName;
  this->os << "Input project name: ";
  std::getline(this->is, projectName);
  if (projectName != ""){
    Project* newProj = new Project(projectName);
    if (this->currProj == NULL){
      this->setCurrProj(newProj);
    }
    return newProj;
  } else{
    return NULL;
  }
}

Task* TaskManager::create_task(){
  string title, details;
  this->os << "Input task name: ";
  std::getline(this->is,title);
  if (title == ""){ // return NULL if no title entered
    return NULL;
  }
  this->os << "Input description of task (or leave empty):" << std::endl;
  std::getline(this->is,details);
  Task* newTask;
  if (details == ""){
    newTask = new Task(title);
  } else{
    newTask = new Task(title, details);
  }
  if (this->currTask == NULL){
    this->setCurrTask(newTask);;
  }
  return newTask;
}

void TaskManager::setCurrProj(Project* p){
  this->os << "Setting \"" << p->getName() << "\" to current project..." << std::endl;
  this->currProj = p;
}

void TaskManager::setCurrTask(Task* t){
  this->os << "Setting \"" << t->getTitle() << "\" to current task..." << std::endl;
  this->currTask = t;
}

// Execute

int TaskManager::exec(string cmd){
  vector<string> splitBySpace = split(cmd, ' ');
  if (splitBySpace.size() == 0){
    return 0; // no command entered
  }
  if (splitBySpace[0] == "make" || splitBySpace[0] == "create"){
   if (splitBySpace.size() == 1){
      this->os << "Must specificy which object to " << splitBySpace[0] << std::endl;
      return 1;
    }
   if (splitBySpace[1] == "project"){
      return cmd_create_and_add_project();
   } else if (splitBySpace[1] ==  "task"){
      return cmd_create_and_add_task();
   } else{
      this->os << "Cannot create object of type \"" << splitBySpace[1] << "\""
	       << std::endl;
      return 1;
   }
  } else if (splitBySpace[0] == "display" || splitBySpace[0] == "show"){
    if (splitBySpace.size() == 1){
      return cmd_display_all_projects();
    }

    if (splitBySpace[1] == "project"){
      return cmd_display_current_project();
    } else if (splitBySpace[1] == "task") {
      return cmd_display_current_task();
    } else if (splitBySpace[1] == "all" || splitBySpace[1] == "projects"){
      return cmd_display_all_projects();
    } else{
      this->os << "Cannot display \"" << splitBySpace[1] << "\""
	       << std::endl;
      return 1;
    }
  } else {
    return 1;
  }
}

void TaskManager::print_blankline(){
  this->os << std::endl;
}

/*
int TaskManager::exec(string cmd){
  this->os << "This is a hard-coded test" << std::endl;
  cmd_create_and_add_project();
  cmd_create_and_add_task();
  cmd_create_and_add_task();
  cmd_display_all_projects();
  cmd_display_current_project();
  cmd_display_current_task();
  return 0;
}
*/

// Commands

int TaskManager::cmd_create_and_add_project(){
  Project* proj = this->create_project();
  if (proj == NULL){
    this->os << "ERROR: Project was not created!" << std::endl;
    return 1;
  }
  this->os << "Project " << proj->getName() << " added as Project #"
	   << projects->size() << std::endl;
  projects->push_back(proj);
  return 0;
}

int TaskManager::cmd_create_and_add_task(){
  if (currProj == NULL){
    this->os << "ERROR: You must have a project to create a task!" << std::endl;
    return 1;
  }
  Task* task = this->create_task();
  if (task == NULL){
    this->os << "ERROR: Task was not created!" << std::endl;
    return 1;
  }
  this->os << "Task " << task->getTitle() << " created and added to Project "
	   << currProj->getName() << std::endl;
  this->currProj->addTask(task);
  return 0;
}

int TaskManager::cmd_display_all_projects(){
  for (int i=0;i<projects->size();i++){
    this->os << i << "\t" << projects->at(i)->getName() << std::endl;
  }
  return 0;
}

int TaskManager::cmd_display_current_project(){
  if (currProj == NULL){
    this->os << "No current project" << std::endl;
    return 1;
  }
  this->os << *currProj << std::endl;
  return 0;
}

int TaskManager::cmd_display_current_task(){
  if (currTask == NULL){
    this->os << "No current task" << std::endl;
    return 1;
  }
  this->os << *currTask << std::endl;
  return 0;
}
