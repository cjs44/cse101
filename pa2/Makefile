# Caitlin Smith - csmith44 
# 2023 Winter CSE101 PA2 
# Makefile 
# Makefile for PA2 

#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 2
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in7
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindPath GraphClient GraphTest FindPath.o GraphClient.o GraphTest.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) FindPath in7 junk7

checkClient : GraphClient
	$(MEMCHECK) GraphClient

checkTest : GraphTest
	$(MEMCHECK) GraphTest
