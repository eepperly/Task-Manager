#ifndef _PROJECT_H
#define _PROJECT_H

#include <vector>
#include <string>

#include "task.h"

class Project{
 public:
  Project(std::string name);
  void addTask(Task* t);
  const std::vector<Task*> & getTasks() const;
  std::string getName() const;
  friend ostream &operator << (ostream &os, Project &p);
  std::string getJSON() const;
 private:
  std::string name;
  std::vector<Task*> tasks;
};

#endif // _PROJECT_H
