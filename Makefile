TARGET = eigenvalues
OBJECTS = main.o iohandler.o solution.o
CC = g++
CFLAGS = -std=c++14 -c -Werror -Wall -O3

.DEFAULT_GOAL := $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
  
main.o: main.cpp iohandler.h solution.h accuracy.h
	$(CC) $(CFLAGS) main.cpp
  
  
iohandler.o: iohandler.cpp iohandler.h
	$(CC) $(CFLAGS) iohandler.cpp
  
  
solution.o: solution.cpp solution.h tridiagonal.h
	$(CC) $(CFLAGS) solution.cpp
  
  
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)

