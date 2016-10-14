#ifndef _TASK_H
#define _TASK_H

#include <vector>
#include <string>
#include <iostream>

class Project;

using std::ostream;

class Task{
 public:
  Task(std::string title);
  Task(std::string title, std::string details);
  void addSubtask(Task t);
  std::string getTitle() const;
  std::string getDetails() const;
  const std::vector<Task> & getSubtasks() const;
  void setProject(Project * p);
  friend ostream &operator << (ostream &os, Task &p);
 private:
  std::string title;
  std::string details;
  std::vector<Task> subtasks;
  Project* project;
};

#endif // _TASK_H
