#include <atomic>
#include <thread>
#include <cassert>

std::atomic<bool> x{};
std::atomic<bool> y{};
std::atomic<int> z{};

void write_x_then_y()
{
	x.store(true, std::memory_order_relaxed);
	y.store(true, std::memory_order_relaxed);
}

void read_y_then_x()
{
	while(!y.load(std::memory_order_relaxed)) {
		// Spin ...
	}

	if(x.load(std::memory_order_relaxed)) {
		++z;
	}
}

int main() {
	auto a = std::thread{write_x_then_y};
	auto b = std::thread{read_y_then_x};
	a.join();
	b.join();
	assert(z.load() != 0);
}
