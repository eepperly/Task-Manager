#include <iostream>
#include <string>

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
  this->os << "Setting " << p->getName() << " to current project..." << std::endl;
  this->currProj = p;
}

void TaskManager::setCurrTask(Task* t){
  this->os << "Setting " << t->getTitle() << "to current task..." << std::endl;
  this->currTask = t;
}

// Execute

int TaskManager::exec(string cmd){
  this->os << "This is a hard-coded test" << std::endl;
  cmd_create_and_add_project();
  cmd_create_and_add_task();
  cmd_create_and_add_task();
  cmd_display_current_project();
  cmd_display_current_task();
  return 0;
}

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

int TaskManager::cmd_display_current_project(){
  this->os << *currProj << std::endl;
  return 0;
}

int TaskManager::cmd_display_current_task(){
  this->os << *currTask << std::endl;
  return 0;
}
