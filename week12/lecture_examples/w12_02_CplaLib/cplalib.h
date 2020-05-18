#ifndef CPLALIB_H_
#define CPLALIB_H_

extern "C" {

struct Point {
	int x;
	int y;
};

typedef struct Unicorn * unicorn;

unicorn createUnicorn(char * name);

void disposeUnicorn(unicorn instance);

void printUnicorn(unicorn unicorn);

void printPoint(Point point);

void printInt(int number);

char * getData(int * size);

void freeData(char * data);
}



#endif /* CPLALIB_H_ */
