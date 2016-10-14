#include "task.h"
#include "project.h"

#include <vector>
#include <iostream>
#include <string>

Project::Project(std::string name){
  this->name = name;
}

void Project::addTask(Task* t){
  tasks.push_back(t);
  t->setProject(this);
}

const std::vector<Task*> & Project::getTasks() const{
  return tasks;
}

std::string Project::getName() const{
  return name;
}

ostream &operator << (ostream &os, Project &p){
  os << p.name << std::endl;
  for (Task*& task : p.tasks){
    os << "\t- "<< task->getTitle() << std::endl;
  }
  return os;
}
