CXX=g++
flags=-std=c++11

all: test test_parsing

test: test.o task.o project.o task_manager.o utils.o load_save.o parsing.o
	${CXX} ${flags} test.o task.o project.o utils.o load_save.o parsing.o task_manager.o -o test

test_parsing: test_parsing.cpp parsing.o utils.o
	${CXX} ${flags} parsing.o utils.o test_parsing.cpp -o test_parsing

task_manager.o : task.h project.h utils.h task_manager.h load_save.h task_manager.cpp
	${CXX} ${flags} -c task_manager.cpp

load_save.o : task_manager.h load_save.h load_save.cpp
	${CXX} ${flags} -c load_save.cpp

utils.o: utils.cpp utils.h
	${CXX} ${flags} -c utils.cpp

task.o:	task.cpp task.h project.h
	${CXX} ${flags} -c task.cpp

project.o: project.cpp task.h project.h utils.h
	${CXX} ${flags} -c project.cpp

parsing.o: parsing.cpp parsing.h utils.h
	${CXX} ${flags} -c parsing.cpp

clean:
	rm -f test *.o *~