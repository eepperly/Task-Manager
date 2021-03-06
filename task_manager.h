#ifndef _TASK_MANAGER_H
#define _TASK_MANAGER_H

#include <string>
#include <iostream>
#include <vector>
#include <stack>

#include "project.h"
#include "task.h"

using std::string;
using std::ostream;
using std::istream;
using std::vector;
using std::stack;

class TaskManager{
 public:
  TaskManager(ostream & os, istream & is);
  TaskManager(string fName, ostream & os, istream & is);
  ~TaskManager();
  int exec(string cmd); // return 0 if command executed successfully
  void print_blankline();
  string getJSON() const;
  friend void copy_task_manager(TaskManager& copy_to, TaskManager& copy_from);

  void setCurrProj(Project* p);
  void setCurrTask(Task* t);
  void addProj(Project* p);
 private:
  string fName; // file name of save file
  void setFName(std::string fName);
  
  vector<Project*>* projects;
  vector<Project*>* getProject() const;
  ostream& os;
  istream& is;
  
  Project* currProj;
  Task* currTask;
  Project* getCurrProj() const;
  Task* getCurrTask() const;

  stack<string>* navCmds; 
  
  void save(); // save to fName
  void save(string otherFileName);
  void load(); // load from fName
  void load(string otherFileName);

  Project* create_project();
  Task* create_task();
  Task* create_subtask(Task* task);

  int cmd_create_and_add_project();
  int cmd_create_and_add_task();
  // int cmd_set_current_project();
  // int cmd_set_current_task();
  int cmd_display_all_projects();
  int cmd_display_current_project();
  int cmd_display_current_task();
  int cmd_save();
  int cmd_load();
};

#endif // _TASK_MANAGER_H
