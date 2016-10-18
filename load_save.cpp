#include "load_save.h"

#include "task_manager.h"
#include "project.h"
#include "task.h"

#include <stdio.h>
#include <string>
#include <fstream>

using std::string;
using std::ofstream;

Saver::Saver(TaskManager * task_manager, string fName){
  this->task_manager = task_manager;
  this->fName = fName;
}

void Saver::setTaskManager(TaskManager* task_manager){
  this->task_manager = task_manager;
}

void Saver::setFileName(string fName){
  this->fName = fName;
}

void Saver::save(){
  ofstream ofs;
  remove(fName.c_str());
  ofs.open (this->fName, std::ofstream::out | std::ofstream::app);
  ofs << task_manager->getJSON();
  ofs.close();
}
