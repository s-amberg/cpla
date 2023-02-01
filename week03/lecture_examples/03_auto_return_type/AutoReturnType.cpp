#include <boost/type_index.hpp>
#include <initializer_list>
#include <iostream>


// auto createInitList() {
//   return {1,2,3};
// }

auto createInt() {  // requires body to be known
  std::cout << "creating int\n";
  return 23;
}

auto const lambda = [](auto p) {  // generic lambda
  std::cout << "lambda: type of p: "
            << boost::typeindex::type_id_with_cvr<decltype(p)>() << "\n";
  return p;
};

// auto f(auto p) -> void {
//	std::cout << "f: type of p: " <<
//boost::typeindex::type_id_with_cvr<decltype(p)>() << "\n";
// }

auto main(int argc, char** argv) -> int {
  createInt();
  lambda(23);
  lambda(23.0);
  //	f(23);
  //	f(23.0);
}
