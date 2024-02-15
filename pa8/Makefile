# Caitlin Smith - csmith44 
# 2023 Spring CSE101 PA8
# Makefile 
# Makefile for PA8

#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryTest    makes DictionaryTest
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryTest under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
ADT            = Dictionary
ORDER          = Order
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ORDER_SOURCE   = $(ORDER).cpp
ORDER_OBJECT   = $(ORDER).o
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(ORDER): $(ORDER_OBJECT) $(ADT_OBJECT)
	$(LINK) $(ORDER) $(ORDER_OBJECT) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(ORDER_OBJECT): $(ORDER_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ORDER_SOURCE)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ORDER) $(ORDER_OBJECT) $(ADT_TEST) $(OBJECT) $(ADT_TEST).o $(ADT_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)
