#include "task.h"
#include "project.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

Task::Task(std::string title){
  this->title = title;
  this->details = "";
  this->project = NULL;
}

Task::Task(std::string title, std::string details){
  this->title = title;
  this->details = details;
  this->project = NULL;
}

void Task::addSubtask(Task t){
  this->subtasks.push_back(t);
}

std::string Task::getTitle() const{ return title; }

std::string Task::getDetails() const{ return details; }

const std::vector<Task> & Task::getSubtasks() const{ return subtasks; }

void Task::setProject(Project* p){
  project = p;
}

ostream &operator << (ostream &os, Task &t){
  os << t.getTitle() << std::endl;
  for (Task& subtask : t.subtasks){
    os << "\t* " << subtask.getTitle() << std::endl;
  }
  return os;
}

std::string Task::getJSON() const{
  std::ostringstream oss;
  oss << "{" << std::endl;
  oss << "  \"title\": \"" << title << "\"," << std::endl;
  oss << "  \"details\": \"" << details << "\"" << std::endl;
  oss << "}";
  return oss.str();
}
