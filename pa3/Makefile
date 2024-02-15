# Caitlin Smith - csmith44 
# 2023 Spring CSE101 PA3 
# Makefile 
# Makefile for PA3 

#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 3
#
#  make                     makes FindComponents
#  make GraphClient         makes GraphClient
#  make GraphTest           makes GraphTest
#  make clean               removes binaries
#  make checkFind           tests FindComponents for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#  make checkTest           tests GraphTest for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindComponents.o : FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindComponents GraphClient GraphTest FindComponents.o GraphClient.o GraphTest.o $(BASE_OBJECTS)

checkFind : FindComponents
	$(MEMCHECK) FindComponents in8 junk8

checkClient : GraphClient
	$(MEMCHECK) GraphClient

checkTest : GraphTest
	$(MEMCHECK) GraphTest
