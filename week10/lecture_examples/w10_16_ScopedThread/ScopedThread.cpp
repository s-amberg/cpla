#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>

struct ScopedThread {
  explicit ScopedThread(std::thread && t)
      : the_thread { std::move(t) } {
    if (!the_thread.joinable())
      throw std::logic_error { "no thread" };
  }
  ~ScopedThread() {
    the_thread.join();
  }
private:
  std::thread the_thread;
};

int main() {
  ScopedThread t { std::thread {
    [] {std::cout << "Hello Thread"<< std::endl;}
  }};
  std::cout << "Hello Main" << std::endl;
}
