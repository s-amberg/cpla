#ifndef FANCYPP
#define FANCYPP

extern "C" {
#include "fancy.h"
}
#include <string>

namespace cppug {

inline void be_fancy(std::string entity) {
	cppug_be_fancy_on_stdout(entity.c_str());
}

}

#endif
