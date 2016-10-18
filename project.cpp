#include "task.h"
#include "project.h"
#include "utils.h"

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

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

std::string Project::getJSON() const{
  std::ostringstream oss;
  oss << "{" << std::endl;
  oss << "  \"name\": \"" << name << "\"," << std::endl;
  oss << "  \"tasks\": [" << std::endl;
  if (tasks.size() > 1){
    for (int i=0;i<tasks.size()-1;i++){
      oss << indent(tasks.at(i)->getJSON(),"  ") << "," << std::endl;
    }
  }
  if (tasks.size() != 0){
    oss << indent(tasks.back()->getJSON(), "  ") << std::endl;
  }
  oss << "  ]" << std::endl;
  oss << "}";
  return oss.str();
}
