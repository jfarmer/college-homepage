CC=g++
CFLAGS=-c -Wall -O3
LDFLAGS=
SOURCES=main.cpp Parse.cpp Lexicon.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=suffixes

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
