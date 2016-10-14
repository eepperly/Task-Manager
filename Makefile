CXX=g++

test: test.o task.o project.o
	${CXX} test.o task.o project.o -o test

task.o:	task.cpp task.h project.h
	${CXX} -c task.cpp

project.o: project.cpp task.h project.h
	${CXX} -c project.cpp

clean:
	rm -f test *.o *~