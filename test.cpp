#include "project.h"
#include "task.h"
#include <iostream>

int main(){
  Project proj1 = Project("General");
  Project proj2 = Project("School");

  Task task1 = Task("Make Toast");
  Task task2 = Task("Organize Backpack");
  Task task3 = Task("Do Homework");

  task2.addSubtask( Task("Clean Binder") );
  task2.addSubtask( Task("Pack Lunch") );

  proj1.addTask(&task1);
  proj1.addTask(&task2);
  proj2.addTask(&task3);

  std::cout << proj1;
  std::cout << proj2;
  std::cout << task2;
  

  return 0;
}
