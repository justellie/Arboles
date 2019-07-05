TARGET = test
LIBS = -lm
CC = g++ -g
CFLAGS = -g -Wall
.PHONY: default all clean
default: $(TARGET)
all: default
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
HEADERS = $(wildcard *.h)
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
.PRECIOUS: $(TARGET) $(OBJECTS)
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@
clean:
	-rm -f *.o core
cleanall: clean
	-rm -f $(TARGET)	
