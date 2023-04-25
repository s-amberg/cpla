#include <atomic>
#include <thread>
#include <iostream>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x() {
	x.store(true, std::memory_order_release);
}

void write_y() {
	y.store(true, std::memory_order_release);
}

void read_x_then_y() {
	while (!x.load(std::memory_order_acquire));
	if (y.load(std::memory_order_acquire)) ++z;
}

void read_y_then_x() {
	while (!y.load(std::memory_order_acquire));
	if (x.load(std::memory_order_acquire)) ++z;
}

int main() {
	x = false;
	y = false;
	z = 0;
	auto c = std::thread(read_x_then_y);
	auto d = std::thread(read_y_then_x);
	auto a = std::thread(write_x);
	auto b = std::thread(write_y);
	a.join();
	b.join();
	c.join();
	d.join();
	std::cout << "z == " << z << '\n';
}
