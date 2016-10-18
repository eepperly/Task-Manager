#ifndef _LOAD_SAVE_H
#define _LOAD_SAVE_H

#include <string>
#include "task_manager.h"

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

#endif // _LOAD_SAVE_H
