.PHONY: test
build: main.cpp solution.cpp iohandler.cpp
	g++ main.cpp solution.cpp iohandler.cpp -O3 -Wall -Werror -o eigenvalues

test1: eigenvalues
	./eigenvalues 300 10 2e-12 1

test2: eigenvalues
	./eigenvalues 300 10 2e-12 2

test3: eigenvalues
	./eigenvalues 300 10 2e-12 3


test4: eigenvalues
	./eigenvalues 300 10 2e-12 4


