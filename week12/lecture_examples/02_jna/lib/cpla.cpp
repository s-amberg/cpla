#include "cplalib.h"

#include <iostream>
#include <string>

extern "C" {

struct Unicorn {
  std::string name;
};

unicorn createUnicorn(char *name) {
  return new Unicorn{name};
}

void disposeUnicorn(unicorn instance) {
  delete instance;
}

void printUnicorn(unicorn unicorn) {
  std::cout << "unicorn: " << unicorn->name << '\n' << std::flush;
}

void printPoint(Point point) {
  std::cout << "x = " << point.x << "y = " << point.y << '\n' << std::flush;
}

void printInt(int number) {
  std::cout << number << '\n' << std::flush;
}

char *getData(int *size) {
  *size = 4;
  return new char[4]{'a', 'b', 'c', 'd'};
}

void freeData(char *data) {
  delete[] data;
}
}
