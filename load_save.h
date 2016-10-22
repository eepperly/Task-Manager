#ifndef _LOAD_SAVE_H
#define _LOAD_SAVE_H

#include <string>
#include "task_manager.h"
#include "parsing.h"

using std::string;

class Saver{
 public:
  Saver(TaskManager* task_manager,string fName);
  void save();
  void setTaskManager(TaskManager* task_manager);
  void setFileName(string fName);
 private:
  TaskManager* task_manager;
  string fName;
};

class Loader{
 public:
  Loader(TaskManager* task_manager,string fName);
  int load(); // 0 if successful
  void setTaskManager(TaskManager* task_manager);
  void setFileName(string fName);
  TaskManager* getTaskManager() const;
 private:
  TaskManager* task_manager;
  string fName;
  Task* taskFromTree(Tree* tree) const;
  Project* projectFromTree(Tree* tree) const;
  TaskManager* taskManagerFromTree(Tree* tree) const;
};

#endif // _LOAD_SAVE_H
