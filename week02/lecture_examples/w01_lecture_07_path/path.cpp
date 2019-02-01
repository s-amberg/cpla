#include <iostream>

#if USE_STD_FS
#include <filesystem>
namespace fs = std::filesystem;
#else
//requires library: boost_filesystem
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#endif

int main() {
  using std::cout;
  fs::path const p{"./Hallo"};
  cout << p << '\n';
  if (is_directory(p)) {
    cout << " DIR exists" << '\n';
    fs::remove(p);
  } else {
    cout << "creating dir " << p ;
    if (fs::create_directory(p))
      cout << " success";
    else
      cout << " failed";
    cout << '\n';
  }
}
