CXX=g++
flags=-std=c++11

test: test.o task.o project.o task_manager.o
	${CXX} ${flags} test.o task.o project.o task_manager.o -o test

task_manager.o : task.h project.h task_manager.h task_manager.cpp
	${CXX} ${flags} -c task_manager.cpp

task.o:	task.cpp task.h project.h
	${CXX} ${flags} -c task.cpp

project.o: project.cpp task.h project.h
	${CXX} ${flags} -c project.cpp

clean:
	rm -f test *.o *~