#include "LineIterator.h"

#include <iterator>
#include <iostream>


int main(){
	LineIterator input_iter{std::cin};
	LineIterator eof{};
	std::cout << std::distance(input_iter, eof);
}


