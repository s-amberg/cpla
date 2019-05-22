OBJECTS = main.o frobnify.o discombobulate.o

all: frobnibulator

frobnibulator: $(OBJECTS)
	g++ -o frobnibulator  $^ 

%.o: %.cpp
	g++ -c $<
