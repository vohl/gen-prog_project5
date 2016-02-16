config:
	doxygen -g

all:

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f Graph.log
	rm -f TestGraph
	rm -f TestGraph.out
	rm -f vohl0803-TestGraph.c++
	rm -f vohl0803-TestGraph.out
	rm -rf html

doc:
	doxygen Doxyfile

log:
	git log > graph.log

TestGraph: Graph.h TestGraph.c++
	g++-4.7 -W -pedantic -std=c++11 -fprofile-arcs -ftest-coverage TestGraph.c++ -o TestGraph -lgtest -lpthread -lgtest_main

coverage:
	valgrind ./TestGraph 
	gcov-4.7 -b Graph.h TestGraph.c++

final_push:
	gcov-4.7 -b TestGraph.c++ > TestGraph.out 2>&1
	./TestGraph > vohl0803-TestGraph.out
	cat TestGraph.out >> vohl0803-TestGraph.out 
	./TestGraph > TestGraph.out
	cp TestGraph.c++ vohl0803-TestGraph.c++
